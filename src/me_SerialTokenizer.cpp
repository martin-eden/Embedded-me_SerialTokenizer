// Getting entity from Serial

/*
  "Entity" is a non-gap sequence surrounded by "spaces".

  "Space" is space character, newline or "end of stream" condition.
*/

/*
  Author: Martin Eden
  Last mod.: 2024-06-07
*/

#include "me_SerialTokenizer.h"

#include <HardwareSerial.h> // Serial: available(), peek(), getTimeout(), read()
#include <Arduino.h> // delay()
#include <ctype.h> // isspace()

#include <me_MemorySegment.h>
#include <me_BaseTypes.h>

using namespace me_BaseTypes;
using namespace me_MemorySegment;
using namespace me_SerialTokenizer;

/*
  Get entity from serial stream.

  Input

    TMemorySegment Buffer

      Memory segment where we will store bytes.

      It IS NOT data to parse. We are obtaining data to parse from
      Serial.

  Output

    TCapturedEntity

      .Segment - Subsegment in buffer where we have bytes.
      .IsTrimmed - Entity would be longer if buffer was larger.

  Behavior

    We do not wait for non-space characters.

      If the stream was empty or only spaces were received then

        TCapturedEntity.Segment.Size == 0
*/
TBool me_SerialTokenizer::GetEntity(
  TCapturedEntity * EntityPtr,
  TMemorySegment Buffer
)
{
  TCapturedEntity Result;

  Result.Segment.Start = Buffer.Start;
  // Now <Segment> starts at the same memory as <Buffer>

  Result.Segment.Size = 0;

  Result.IsTrimmed = false;

  *EntityPtr = Result;

  if (Buffer.Size == 0)
    // you gonna be kidding me!
    return false;

  PurgeSpaces();

  // Pre condition: buffer size >= 1, stream is empty or at non-space
  TChar Char;
  while (PeekCharacter(&Char))
  {
    if (isspace(Char))
      break;

    PurgeCharacter();

    // copy character to memory address
    Buffer.Bytes[Result.Segment.Size] = Char;

    // increase size
    ++Result.Segment.Size;

    // no place to store more?
    if (Result.Segment.Size == Buffer.Size)
    {
      Result.IsTrimmed = PurgeEntity();

      break;
    }
  }
  // Post-condition: stream is empty or at space

  *EntityPtr = Result;

  if (Result.Segment.Size == 0)
    return false;

  return true;
}

/*
  Wait entity from serial stream

  We will not return until we get something non-empty.
*/
void me_SerialTokenizer::WaitEntity(
  TCapturedEntity * Entity,
  TMemorySegment Buffer
)
{
  while(!GetEntity(Entity, Buffer));
}

/*
  Drop characters from stream
  until
    non-space character or
    end of stream
*/
void me_SerialTokenizer::PurgeSpaces()
{
  TChar Char;
  while (true)
  {
    if (!PeekCharacter(&Char))
      return;

    if (!isspace(Char))
      return;

    PurgeCharacter();
  }
}

/*
  Return next character in stream but do not extract it.

  Implementation will wait for some time if stream is currently empty.
*/
TBool me_SerialTokenizer::PeekCharacter(TChar * Char)
{
  if (StreamIsEmpty())
    delay(Serial.getTimeout());

  return StockPeek(Char);
}

// Return true when serial stream is empty.
TBool me_SerialTokenizer::StreamIsEmpty()
{
  return (Serial.available() == 0);
}

/*
  Return next character in stream but do not consume it.

  Implemented as wrapper over stock Serial.peek().
*/
TBool me_SerialTokenizer::StockPeek(TChar * Char)
{
  TSint_2 PeekResult = Serial.peek();

  // Empty stream?
  if (PeekResult == -1)
    return false;

  *Char = PeekResult;

  // printf("[%c]", *Char);

  return true;
}

/*
  Drop one character from the stream.

  Intended use is to peek character before calling this function.
*/
void me_SerialTokenizer::PurgeCharacter()
{
  if (StreamIsEmpty())
    return;

  Serial.read();
}

/*
  Drop characters from stream
  until
    space character or
    end of stream

  Returns true when at least one non-space character was dropped.
*/
TBool me_SerialTokenizer::PurgeEntity()
{
  TChar Char;
  TBool PurgedSomething = false;

  while (true)
  {
    if (!PeekCharacter(&Char))
      return PurgedSomething;

    if (isspace(Char))
      return PurgedSomething;

    PurgeCharacter();

    PurgedSomething = true;
  }

  return PurgedSomething;
}

/*
  2024-05-08
  2024-05-13
  2024-05-19 [>~] Interface arguments are records now
*/
