/*
 * Locker_System.c
 *
 * Created: 9/8/2023 10:49:57 AM
 *  Author: C O N N E C T
 */ 


#include "LCD.h"
#include "KEYPAD.h"
#include "EEPROM.h"
#define Buzzer SETBIT(PORTB,PB0); _delay_ms(100); CLRBIT(PORTB,PB0);

uint8_t User_pass[11]={'0','0','0','0','/'};
	
int main(void)
{
	SETBIT(DDRB,PB0);
	uint8_t j,pass_pro[10]={'0','1','2','3','4','5','6','7','8','9'},Entered_pass[10],counter=0;
	LCD_init();
	KEYPAD_init();
	
    while(1)
    {
		//if user input wrong password 3 times
		if(counter==3){
			LCD_write_command(1);
			LCD_write_string("For next try:");
			for(j=10;j>0;j--){
				LCD_write_command(Second_Line(0));
				LCD_write_string("wait ");
				LCD_write_num(j);
				LCD_write_string("sec");
				LCD_write_string(" ");
				_delay_ms(1000);
			}
			counter=0;
			LCD_write_command(1); 
		}
		
		
		uint8_t i=0,flag=1,check=1;
				
		LCD_write_command(First_Line(1));
		LCD_write_string("Enter the pass");
		
		//return password from EEPROM
		if(EEPROM_read(19)==2){
			for(j=0;EEPROM_read(20+j)!='/';j++){
				User_pass[j]=EEPROM_read(20+j);
			}
			User_pass[j]='/';
		}
		
		
		/*========================================*Global reset for the password *=====================================*/
		
			while(Key_pressed() == 'x');
			
			/*Password Reset*/
			if(Key_pressed()=='-'){
				Buzzer;
				while(Key_pressed() != 'x');
				LCD_write_command(0x01);
				LCD_write_command(First_Line(0));
				LCD_write_string("GlobalPassReset");
				LCD_write_command(Second_Line(0));
				for(i=0;i<10;i++){
				while(Key_pressed() == 'x');
				if(Key_pressed()=='-') {break; Buzzer;}
				Buzzer;
				LCD_write_command(Second_Line(i));
				LCD_write_char('*');
				Entered_pass[i]=Key_pressed();
				while(Key_pressed()!='x');
				}
				
			
			/*Compare*/
			flag=1;
			for(i=0; i<10 ;i++){
				if(pass_pro[i] == Entered_pass[i]) {
					continue;
				}
				else {
					LCD_write_command(Second_Line(0));
					LCD_write_string("Wrong pass");
					_delay_ms(500);
					flag=0;
					break;
				}
			}
			if(flag == 0) {LCD_write_command(0x01); continue;}
			if(flag == 1) {
				LCD_write_command(0x01);
				LCD_write_command(First_Line(0));
				LCD_write_string("Password Reset");
				_delay_ms(500);
				LCD_write_command(0x01);
				for(i=0;i<4;i++){
					EEPROM_write(20+i,'0');
				}
				EEPROM_write(20+i, '/');
				EEPROM_write(19,2);
			}
			continue;
			}				
						
		/*============================================*Reset the passsword*============================================*/
		
		if(Key_pressed() == '/'){
			SETBIT(PORTB,PB0); _delay_ms(1000); CLRBIT(PORTB,PB0);
			while(check){
			flag=1;
			LCD_write_command(0x01);
			LCD_write_command(First_Line(1));
			LCD_write_string("Reset the pass");
			_delay_ms(500);
			
			/*Check current password*/
			LCD_write_command(0x01);
			LCD_write_command(First_Line(2));
			LCD_write_string("Current pass");
			
			while(Key_pressed() != 'x');
			while(Key_pressed() == 'x');
			if(Key_pressed() == '/') {Buzzer; while(Key_pressed() != 'x'); break;}
						
			/*Take password*/
			for(i=0;User_pass[i] != '/';i++){
				while(Key_pressed() == 'x');
				Buzzer;
				LCD_write_command(Second_Line(i));
				Entered_pass[i]= Key_pressed();
				LCD_write_char('*');
				while(Key_pressed() != 'x');
			}
		
			/*Compare the password*/
			for(i=0; User_pass[i] != '/' ;i++){
				if(User_pass[i] == Entered_pass[i]) {
					continue;
				}
				else {
					LCD_write_command(0x01);
					LCD_write_string("Wrong pass");
					_delay_ms(500);
					flag=0;
					break;
				}
			}
			
			/*Enter new password*/
			if(flag==1) {
				check=0;
				LCD_write_command(0x01);
				LCD_write_command(First_Line(4));
				LCD_write_string("New pass");
				
				for(i=0;i<10;i++){
					while(Key_pressed() == 'x');
					Buzzer;
					if(Key_pressed() == '/') { break;}
					LCD_write_command(Second_Line(i));
					User_pass[i]= Key_pressed();
					LCD_write_char('*');
					while(Key_pressed() != 'x');
				}
				User_pass[i]='/';
				LCD_write_command(0x01); 
				while(Key_pressed() != 'x');
				}
			
			}
			
			//save password in EEPROM
			for(i=0;User_pass[i]!='/';i++){
				EEPROM_write(20+i, User_pass[i]);
			}
			EEPROM_write(20+i, '/');
			EEPROM_write(19,2);
			continue;
		}		
		
		
		/*============================================*Take password from user*============================================*/
		
		LCD_write_command(First_Line(1));
		LCD_write_string("Enter the pass");
		
		for(i=0;User_pass[i] != '/';i++){
		while(Key_pressed() == 'x');
		Buzzer;
		LCD_write_command(Second_Line(i));
		Entered_pass[i]= Key_pressed();	
		LCD_write_char('*');
		while(Key_pressed() != 'x');		
		}
		
		
		/*===================================*Compare password entered with the saved password*===============================*/
						
		flag=1;				
		for(i=0; User_pass[i] != '/' ;i++){
			if(User_pass[i] == Entered_pass[i]) {
				continue;
			}				
			else { 
				LCD_write_command(Second_Line(0));
				LCD_write_string("Wrong pass"); 
				_delay_ms(500);
				flag=0;
				counter++;
				break;
				}
		}
		if(flag == 0) {LCD_write_command(0x01); continue;}		
		if(flag == 1) {
			LCD_write_command(0x01);
			LCD_write_command(First_Line(1));
			LCD_write_string("locker Opened");	
			
			//Close the locker
			while(Key_pressed()!='*');
			Buzzer;
			LCD_write_command(0x01);
			LCD_write_command(First_Line(1));
			LCD_write_string("locker Closed");
			_delay_ms(500);
			LCD_write_command(0x01);
			while(Key_pressed()!='x');		
		}
			
	}	
}