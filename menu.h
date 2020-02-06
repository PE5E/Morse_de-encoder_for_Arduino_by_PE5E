void print_menu() {
  Serial.println("Enter some text to hear it in morse.");
  Serial.println("or enter: *** followed by a command from below:");
  Serial.println("- \"keying\" to switch to key input decoded to text");
  Serial.println("- \"playmorse\" to switch to playing text in morse sounds");
  Serial.println("- \"speed\" followed by a number for play speed (e.g. 250 = 0.25 sec)");
  Serial.println("- \"frequency\" followed by a number for the sound frequency (e.g. 900)");
}

bool is_menu_input(String input) {
  if(!input.startsWith("***")) {
    return false;
  }
  
  input.remove(0,3); // remove the ****

  Serial.print("command received: ");
  Serial.println(input);

  if(input.startsWith("speed")) {
    input.remove(0,5);
    if(input.toInt() > 0) {
      unit_length = input.toInt();
      Serial.print("Speed is now ");
      Serial.println(unit_length);
      return true;
    }
  }

  if(input.startsWith("frequency")) {
    input.remove(0,9);
    if(input.toInt() > 0) {
      frequency = input.toInt();
      Serial.print("Frequency is now ");
      Serial.println(frequency);
      return true;
    }
  }
    
  if(input.equals("keying")) {
    p_mode = program_mode::record;
    Serial.println("Switched to keying mode");
    return true;
  }

  if(input.equals("playmorse")) {
    p_mode = program_mode::play;
    Serial.println("Switched to playing mode");
    return true;
  }

  print_menu();  // for everything not catched, including help
  return true;
  
}
