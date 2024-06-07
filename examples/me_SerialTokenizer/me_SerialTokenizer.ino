// Stream tokenizer demo

/*
  Enter random space/newline separated strings to Serial.

  Non-space sequences are caught by GetEntity() and printed.
*/

/*
  Author: Martin Eden
  Last mod.: 2024-06-08
*/

#include <me_SerialTokenizer.h>
#include <me_MemorySegment.h>

#include <me_InstallStandardStreams.h>
#include <me_UartSpeeds.h>
#include <me_BaseTypes.h>

// Forwards
void RunTest();

void setup()
{
  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);
  Serial.setTimeout(10);
  InstallStandardStreams();

  printf("[me_SerialTokenizer] Okay, we are here.\n");
  Test();
  printf("Done.\n");
}

void loop()
{
}

void Test()
{
  using
    me_BaseTypes::TChar,
    me_BaseTypes::TUint_2,
    me_MemorySegment::TMemorySegment,
    me_SerialTokenizer::TCapturedEntity,
    me_SerialTokenizer::WaitEntity;

  const TUint_2 EntityMaxLength = 8;

  TChar Buffer[EntityMaxLength];

  TMemorySegment BufferSeg;
  BufferSeg.Start.Addr = (TUint_2) &Buffer;
  BufferSeg.Size = sizeof(Buffer);

  TCapturedEntity Capture;

  printf("We are capturing space-separated entries from serial input.\n");
  printf("Maximum entry length: %u\n", EntityMaxLength);
  printf("\n");
  printf("Type 'exit' to leave.\n");

  TUint_2 EntityCounter = 0;
  while (true)
  {
    WaitEntity(&Capture, BufferSeg);

    ++EntityCounter;

    printf("[%u] ", EntityCounter);
    printf("%u ", Capture.Segment.Size);
    printf("(");
    Capture.Segment.Print();
    printf(")");
    if (Capture.IsTrimmed)
      printf("..");
    printf("\n");

    if (Capture.Segment.IsEqualTo("exit"))
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
*/
