// Stream tokenizer demo

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

/*
  Enter random space/newline separated strings.

  Non-space sequences are caught, added to list and
  printed by "print" command.
*/

/*
  FIXME

    Double "clear" and then "print" prints infinite "clear" string.
    Need to investigate

      > clear
      > clear
      > print
      < clear
      < clear
      < ...

    -- Martin, 2024-12-20

    This ancient code is still broken. Need to investigate (or review
    design).

    -- Martin, 2025-08-27
*/

#include <me_SerialTokenizer.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_Menu.h>

#include <me_WorkmemTools.h>

// Forwards
void RunTest();

void setup()
{
  Console.Init();

  Console.Print("[me_SerialTokenizer] Okay, we are here.");
  Test();
  Console.Print("[me_SerialTokenizer] Done.");
}

void loop()
{
}

void Test()
{
  const TUint_2 EntityMaxLength = 8;

  TUint_1 Buffer[EntityMaxLength];

  TAddressSegment BufferSeg =
    { .Addr = (TAddress) &Buffer, .Size = sizeof(Buffer) };

  TAddressSegment Capture;

  Console.Print("We are capturing space-separated entries from serial input.");

  Console.Write("Maximum entry length:");
  Console.Print(BufferSeg.Size);
  Console.EndLine();

  Console.Print("Type 'print' to print list.");
  Console.Print("Type 'clear' remove items from list.");
  Console.Print("Type 'exit' to leave.");

  me_SerialTokenizer::TSerialTokenizer Tokenizer;
  Tokenizer.BreakTimeout_ms = 5000;
  /*
    We're using [me_Menu] just to store and print list of strings.
    Ironically, [me_Menu] uses us to get command from stream.
    But we're not using that facility here.
  */

  me_Menu::TMenu List;

  while (true)
  {
    Tokenizer.WaitEntity(&Capture, BufferSeg);

    if (IsExitCommand(Capture))
      break;

    if (IsClearCommand(Capture))
      ReleaseList(&List);

    if (IsPrintCommand(Capture))
      PrintList(&List);

    AddToList(&List, Capture);
  }

  ReleaseList(&List);
}

TBool IsExitCommand(
  TAddressSegment Text
)
{
  using
    me_WorkmemTools::FromAsciiz,
    me_WorkmemTools::AreEqual;

  return AreEqual(Text, FromAsciiz("exit"));
}

TBool IsClearCommand(
  TAddressSegment Text
)
{
  using
    me_WorkmemTools::FromAsciiz,
    me_WorkmemTools::AreEqual;

  return AreEqual(Text, FromAsciiz("clear"));
}

TBool IsPrintCommand(
  TAddressSegment Text
)
{
  using
    me_WorkmemTools::FromAsciiz,
    me_WorkmemTools::AreEqual;

  return AreEqual(Text, FromAsciiz("print"));
}

void AddToList(
  me_Menu::TMenu * List,
  TAddressSegment Item
)
{
  TAddressSegment CommandSeg;
  me_Menu::TMenuItem MenuItem;

  me_WorkmemTools::Reserve(&CommandSeg, Item.Size);
  me_WorkmemTools::CopyMemTo(CommandSeg, Item);

  MenuItem.Command = CommandSeg;

  List->AddItem(MenuItem);
}

void PrintList(
  me_Menu::TMenu * List
)
{
  List->Print();
}

void ReleaseList(
  me_Menu::TMenu * List
)
{
  List->Release();
}

/*
  2024 # # # # # # # #
*/
