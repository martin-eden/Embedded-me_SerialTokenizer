// Stream tokenizer demo

/*
  Author: Martin Eden
  Last mod.: 2024-12-20
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
*/

#include <me_BaseTypes.h>
#include <me_Uart.h>
#include <me_Console.h>
#include <me_MemorySegment.h>
#include <me_SerialTokenizer.h>
#include <me_Menu.h>

// Forwards
void RunTest();

void setup()
{
  me_Uart::Init(me_Uart::Speed_115k_Bps);

  Console.Print("[me_SerialTokenizer] Okay, we are here.");
  Test();
  Console.Print("[me_SerialTokenizer] Done.");
}

void loop()
{
}

void Test()
{
  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::FromAddrSize,
    me_SerialTokenizer::TSerialTokenizer;

  const TUint_2 EntityMaxLength = 8;

  TUint_1 Buffer[EntityMaxLength];

  TMemorySegment BufferSeg =
    FromAddrSize((TUint_2) &Buffer, sizeof(Buffer));

  TMemorySegment Capture;

  Console.Print("We are capturing space-separated entries from serial input.");
  Console.Write("Maximum entry length:");
  Console.Print(BufferSeg.Size);
  Console.EndLine();
  Console.Print("Type 'print' to print list.");
  Console.Print("Type 'clear' remove items from list.");
  Console.Print("Type 'exit' to leave.");

  TSerialTokenizer Tokenizer;
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
  me_MemorySegment::TMemorySegment Text
)
{
  using
    me_MemorySegment::Freetown::FromAsciiz,
    me_MemorySegment::Freetown::AreEqual;

  return AreEqual(Text, FromAsciiz("exit"));
}

TBool IsClearCommand(
  me_MemorySegment::TMemorySegment Text
)
{
  using
    me_MemorySegment::Freetown::FromAsciiz,
    me_MemorySegment::Freetown::AreEqual;

  return AreEqual(Text, FromAsciiz("clear"));
}

TBool IsPrintCommand(
  me_MemorySegment::TMemorySegment Text
)
{
  using
    me_MemorySegment::Freetown::FromAsciiz,
    me_MemorySegment::Freetown::AreEqual;

  return AreEqual(Text, FromAsciiz("print"));
}

void AddToList(
  me_Menu::TMenu * List,
  me_MemorySegment::TMemorySegment Item
)
{
  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::Reserve,
    me_MemorySegment::Freetown::CopyMemTo,
    me_Menu::TMenuItem,
    me_Menu::Freetown::ToItem;

  TMemorySegment CommandSeg;
  Reserve(&CommandSeg, Item.Size);
  CopyMemTo(CommandSeg, Item);

  TMenuItem MenuItem;
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
  2024-05 # # # # #
  2024-06 #
  2024-10 #
  2024-10 #
*/
