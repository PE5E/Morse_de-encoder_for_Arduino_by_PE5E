void play_morse(String morse_word) {
  for(int i=0; i<=morse_word.length(); i++)
  {
    switch( morse_word[i] )
    {
      case '.': //dit
        tone(speaker, frequency);
        delay(unit_length);
        noTone(speaker);
        delay(unit_length);
        break;

      case '-': //dah
        tone(speaker, frequency);
        delay(unit_length*3);
        noTone(speaker);
        delay(unit_length);
        break;

      case ' ': //gap
        delay(unit_length);
        break;
    }
    Serial.print(morse_word[i]);
  }
  Serial.println("");    // newline
}
