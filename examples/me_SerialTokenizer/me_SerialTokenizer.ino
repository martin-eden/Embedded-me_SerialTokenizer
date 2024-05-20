// Stream tokenizer demo

/*
  Enter random space/newline separated strings to Serial.

  Non-space sequences are caught by GetEntity() and printed.
*/

/*
  Author: Martin Eden
  Last mod.: 2024-05-20
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

  const TUint_2 EntityMaxLength = 3;

  TChar EntityBuf[EntityMaxLength + 1];

  TMemorySegment Buffer =
    {
      .Start = { .Addr = (TUint_2) EntityBuf },
      .Size = sizeof(EntityBuf),
    };

  TEntity Entity;

  printf("We are capturing space-separated entries from serial input.\n");
  printf("Maximum entry length is %u.\n", EntityMaxLength);
  printf("Try input something..\n");

  while (true)
  {
    if (GetEntity(&Entity, Buffer))
    {
      printf("(%s)", Entity.Chars);
      if (Entity.IsTrimmed)
        printf("..");
      printf(" # %u\n", Entity.Length);
    }
  }
}

/*
  2024-05-08
  2024-05-13
  2024-05-17
  2024-05-19
*/
