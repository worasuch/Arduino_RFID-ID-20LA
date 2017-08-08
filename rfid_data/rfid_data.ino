//Example sketch for RFID ID-20LA reader
//More info available at http://tutorial.cytron.com.my/

byte tagID[12];
boolean tagread=false;
int manCount;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
}

void loop()
{

  if(Serial2.available()>=13)      //Make sure all the frame is received
  {
    if(Serial2.read()==0x02)       //Check for the start byte = 0x02
    {
      tagread=true;                //New tag is read
      for(int index=0;index<sizeof(tagID);index++)
      {
        byte val=Serial2.read();
        
        //convert from ASCII value to value range from 0 to 9 and A to F
        if( val >= '0' && val <= '9')
        val = val - '0';
        else if( val >= 'A' && val <= 'F')
        val = 10 + val - 'A';
        
        tagID[index]=val;
      }
    }
    else
    {
      tagread=false;                //Discard and skip
    }
  }

  if(tagread==true)                 //New tag is read
  {
    if(manCount < 5)                //the number of man in room
    {
      manCount++;
      Serial.print("manCount: ");
      Serial.print(manCount);
      Serial.print("\r\n");
      print_tag();                    //Display the tag ID
      clear_tag();                    //Clear the tag ID and ready for next tag
      tagread=false;
    }
    
    if(manCount >= 5)                //the number of man in room
    {
      manCount++;
      Serial.print("manCount: ");
      Serial.print(manCount);
      Serial.print("\r\n");
      //digitalWrite(3, LOW);
      //digitalWrite(4, HIGH);
      print_tag();                    //Display the tag ID
      clear_tag();                    //Clear the tag ID and ready for next tag
      tagread=false; 
    }
  }
  delay(10);
}

void print_tag()                    //Subroutine to display the tagID content
{
  Serial.print("Tag ID: ");        
  for(int index=0;index<10;index++)
  {
    Serial.print(tagID[index],HEX);  //Display tagID
  }
  Serial.print("\r\nName: ");
  //Serial.print("\r\nChecksum: ");
  //Serial.print(tagID[10],HEX);       //Display checksum
  //Serial.println(tagID[11],HEX);
  if(tagID[10] == 0x03 and tagID[11] == 0x02)
  {
    Serial.print("Happ");
    Serial3.print("Happ");
    Serial.print("\r\n");
  }
  else if(tagID[10] == 0x01 and tagID[11] == 0x09)
  {
    Serial.print("Mo");
    Serial3.print("Mo");
    Serial.print("\r\n");
   }
   else if(tagID[10] == 0x0B and tagID[11] == 0x07)
  {
    Serial.print("Baze");
    Serial3.print("Baze");
    Serial.print("\r\n");
   }
   else if(tagID[10] == 0x0E and tagID[11] == 0x02)
  {
    Serial.print("Jake");
    Serial3.print("Jake");
    Serial.print("\r\n");
   }
   else if(tagID[10] == 0x0D and tagID[11] == 0x0C)
  {
    Serial.print("Stam");
    Serial3.print("Stam");
    Serial.print("\r\n");
   }
  else
  {
    Serial.print("Unknow");
    Serial.print("\r\n");
   } 
}

void clear_tag()                    //Subroutine to clear the tagID content
{  
  for(int index=0;index<sizeof(tagID);index++)
  {
    tagID[index]=0;
  }
}
