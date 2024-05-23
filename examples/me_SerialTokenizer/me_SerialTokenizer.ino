// Stream tokenizer demo

/*
  Enter random space/newline separated strings to Serial.

  Non-space sequences are caught by GetEntity() and printed.
*/

/*
  Author: Martin Eden
  Last mod.: 2024-05-23
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

  RunTest();
}

void loop()
{
}

void RunTest()
{
  using namespace me_BaseTypes;
  using namespace me_MemorySegment;
  using namespace me_SerialTokenizer;

  const TUint_2 EntityMaxLength = 8;

  TChar Buffer[EntityMaxLength];

  TMemorySegment BufferSeg =
    {
      .Start = { .Addr = (TUint_2) &Buffer },
      .Size = sizeof(Buffer),
    };

  TCapturedEntity Capture;

  printf("We are capturing space-separated entries from serial input.\n");
  printf("\nMaximum entry length: %u\n\n", EntityMaxLength);
  printf("Enter something...\n");

  TUint_2 EntityCounter = 0;
  while (true)
  {
    if (GetEntity(&Capture, BufferSeg))
    {
      ++EntityCounter;

      printf("[%u] ", EntityCounter);

      printf("%u ", Capture.Segment.Size);

      // note (1)
      printf("(");
      fwrite(Capture.Segment.Start.Bytes, Capture.Segment.Size, 1, stdout);
      printf(")");

      if (Capture.IsTrimmed)
        printf("..");

      printf("\n");
    }
  }
}

/*
  [1]:
    Lack of easy way in C to print N bytes as characters is annoying.
    Let's do fwrite()!

    Related SO's question:

      https://stackoverflow.com/questions/66692599/print-a-string-of-a-given-length
*/

/*
  2024-05-08
  2024-05-13
  2024-05-17
  2024-05-19
  2024-05-23
*/
