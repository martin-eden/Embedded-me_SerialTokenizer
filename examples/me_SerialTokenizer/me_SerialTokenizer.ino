// Stream tokenizer demo

/*
  Enter random space/newline separated strings to Serial.

  Non-space sequences are caught by GetEntity() and printed.
*/

/*
  Author: Martin Eden
  Last mod.: 2024-10-23
*/

#include <me_SerialTokenizer.h>
#include <me_MemorySegment.h>

#include <me_UartSpeeds.h>
#include <me_BaseTypes.h>

#include <me_Console.h>

// Forwards
void RunTest();

void setup()
{
  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);
  Serial.setTimeout(10);

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
    me_MemorySegment::Freetown::FromAsciiz,
    me_MemorySegment::Freetown::AreEqual,
    me_SerialTokenizer::TCapturedEntity,
    me_SerialTokenizer::WaitEntity;

  const TUint_2 EntityMaxLength = 8;

  TChar Buffer[EntityMaxLength];

  TMemorySegment BufferSeg = FromAddrSize((TUint_2) &Buffer, sizeof(Buffer));

  TCapturedEntity Capture;

  Console.Print("We are capturing space-separated entries from serial input.");
  Console.Write("Maximum entry length:");
  Console.Print(EntityMaxLength);
  Console.EndLine();
  Console.EndLine();
  Console.Print("Type 'exit' to leave.");

  TMemorySegment ExitText = FromAsciiz("exit");
  while (true)
  {
    WaitEntity(&Capture, BufferSeg);

    Console.Write("Contents (");
    Console.Write(Capture.Segment);
    Console.Write(")");
    if (Capture.IsTrimmed)
      Console.Write(" IsTrimmed");
    Console.EndLine();

    if (AreEqual(Capture.Segment, ExitText))
      break;
  }
}

/*
  2024-05-08
  2024-05-13
  2024-05-17
  2024-05-19
  2024-05-23
  2024-06-08
  2024-10-23
*/
