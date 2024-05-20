// Getting entity from Serial

/*
  "Entity" is a non-gap sequence surrounded by "gaps".

  "Gap" is space character, newline or "end of stream" condition.
*/

/*
  Author: Martin Eden
  Last mod.: 2024-05-19
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

    Buffer. Memory segment where we can store bytes. It's size is
    usually big enough.

    It IS NOT data to parse. We obtaining data to parse from Serial.

  Output

    Entity record. In this implementation entity data segment starts at
    the same address as given buffer. But the length of segment is
    smaller.

  Special cases

    When data stream is longer than available memory to hold entity

      Purge data stream until gap
      set <.IsTrimmed> flag
*/
TBool me_SerialTokenizer::GetEntity(
  TEntity * EntityPtr,
  TMemorySegment Buffer
)
{
  TEntity Entity = *EntityPtr;

  Entity.Chars = (TChar *) Buffer.Start.Bytes;
  // Now <Entity.Chars> points to the same memory as <Buffer.Start>

  Entity.Length = 0;
  Entity.IsTrimmed = false;

  *EntityPtr = Entity;

  if (Buffer.Size == 0)
    // you gonna be kidding me!
    return false;

  /*
    Entity stores data as ASCIIZ. So it's maximum length is one less
    than buffer size.

    Buffer size = 1 means we don't have any space to get actual
    data.
  */
  if (Buffer.Size == 1)
    return false;

  // ASCIIZ end
  Buffer.Start.Bytes[0] = '\0';

  PurgeSpaces();

  // Pre condition: buffer size >= 2, stream is empty or at non-space
  TChar Char;
  while (PeekCharacter(&Char))
  {
    if (isspace(Char))
      break;

    PurgeCharacter();

    // copy character to memory address
    Buffer.Start.Bytes[Entity.Length] = Char;

    // increase size
    ++Entity.Length;

    // write zero for ASCIIZ
    Buffer.Start.Bytes[Entity.Length] = '\0';

    // no place to store more?
    TUint_2 EntitySize = Entity.Length + 1;
    if (EntitySize == Buffer.Size)
    {
      Entity.IsTrimmed = PurgeEntity();

      break;
    }
  }
  // Post-condition: stream is empty or at space

  *EntityPtr = Entity;

  if (Entity.Length == 0)
    return false;

  return true;
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
