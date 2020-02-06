String encode_morse(const String string)
{
  size_t i, j;
  String morseWord = "";
  
  for( i = 0; i != string.length(); ++i )
  {
    for( j = 0; j < sizeof MorseMap / sizeof *MorseMap; ++j )
    {
      if( toupper(string.charAt(i)) == MorseMap[j].letter )
      {
        morseWord += MorseMap[j].code;
        break;
      }
    }
    morseWord += " "; //Add tailing space to seperate the chars
  }

  return morseWord;  
}
