LiquidCrystal lcd(RS, E, D4, D5, D6 , D7);  //RS, E, DB4, DB5, DB6 e DB7

void loop() 
{
  switch (bomba())
  {
    case 1:
	{
		prtime_1 = ciclo();
		pstime_1 = ciclo();
		rtime_1 = millis()/1000;
		digitalWrite(LAMP_1,LOW);
		break;
	}
    case 2:
	{
		prtime_2 = ciclo();
		pstime_2 = ciclo();
		rtime_2 = millis()/1000;
		digitalWrite(LAMP_2,LOW);
		break;
	}
    case 3:
	{
		prtime_3 = ciclo();
		pstime_3 = ciclo();
		rtime_3 = millis()/1000;
		digitalWrite(LAMP_3,LOW);
		break;
	}
    case 4:
	{
		prtime_4 = ciclo();
		pstime_4 = ciclo();
		rtime_4 = millis()/1000;
		digitalWrite(LAMP_4,LOW);
		break;
	}
    case 5:
	{
		prtime_5 = ciclo();
		pstime_5 = ciclo();
		rtime_5 = millis()/1000;
		digitalWrite(LAMP_5,LOW);
		break;
	}
    case 6:
	{
		prtime_6 = ciclo();
		pstime_6 = ciclo();
		rtime_6 = millis()/1000;
		digitalWrite(LAMP_6,LOW);
		break;
	}
    case 7:
	{
		prtime_7 = ciclo();
		pstime_7 = ciclo();
		rtime_7 = millis()/1000;
		digitalWrite(LAMP_7,LOW);
		 break;
	}
    case 8:
	{
		prtime_8 = ciclo();
		pstime_8 = ciclo();
		rtime_8 = millis()/1000;
		digitalWrite(LAMP_8,LOW);
		break;
	}
    case 9:
	{
		prtime_9 = ciclo();
		pstime_9 = ciclo();
		rtime_9 = millis()/1000;
		digitalWrite(LAMP_9,LOW);
		break;
	}
    case 10:
	{
		prtime_10 = ciclo();
		pstime_10 = ciclo();
		rtime_10 = millis()/1000;
		digitalWrite(LAMP_10,LOW);
		break;
	}
    case 11:
	{
		prtime_11 = ciclo();
		pstime_11 = ciclo();
		rtime_11 = millis()/1000;
		digitalWrite(LAMP_11,LOW);
		break;
	}
	case 12:
	{
		prtime_12 = ciclo();
		pstime_12 = ciclo();
		rtime_12 = millis()/1000;
		digitalWrite(LAMP_12,LOW);
		break;
	}	
	default:
	{
		loop();		
	}
  }
}

int bomba()
{
  lcd.begin(16, 2);
  int posicao = 9;
  int valor = 0;
	txt_bomba();
  while(tecla != 12)
  {
	  keyboard();
	  if(tecla != 13 && tecla != 12 && tecla != 10)
	  {	
		lcd.setCursor(posicao,1);  
		valor *= 10;
		valor += tecla;
		lcd.print(valor,DEC);
	  }
	  if(tecla == 10)
    {
			tecla = 13;
			loop();
    }
  }
  tecla = 13;	
  return valor;
}

int ciclo (void)
{  
  int valor =0;
  int posicao = 9;	
	txt_ciclo();
  while(tecla != 12)
  {	 
	  keyboard();

	  if(tecla != 13 && tecla != 12 && tecla != 10)
	  {	
		if(on_off == 0)
		{
			lcd.setCursor(posicao,1);
		}
		else if(on_off == 1)
		{
			lcd.setCursor(posicao+3,1);
		}	
		valor *= 10;
		valor += tecla;
		lcd.print(valor,DEC);
		tecla = 13;
	  }
	  while(tecla == 10)
    {
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.write("Deseja voltar?");
			keyboard();
			if(tecla == 10)
        {
				txt_ciclo();
				tecla = 13;
				valor = 0;
				}
        else if(tecla == 12)
        {
	      tecla = 13;
          loop();
        }
     }
  }
  tecla = 13;	
  on_off ^= 1;
  return valor;
}

int keyboard (void)
{
int lido = 0, maior = 0, menor = 0, media, c = 0, amostras = 750;
  while(c<amostras)
  {
    
    lido = analogRead(14);
    if(lido<menor || menor == maior)
    {
      menor = lido;
    }
    
    if(lido>=maior)
    {
      maior = lido;
    }

    c++;
    media = (maior + menor)/2;
    if(menor<10)
    {
      maior = 0;
      menor=0;
      c=0;
    }
  }

  while(c>=amostras)
  { 
    if(maior-menor<=15)
    {
      if(649>=menor && maior>=656 || 651<=media && media<=656)
      {
		 tecla = 1;
      }
      else if(527>=menor && maior>=535 || 530<=media && media<=535)
      {
		 tecla = 2;
      }
      else if(827>=menor && maior>=835 || 829<=media && media<=835)
      {
		 tecla = 3;
      }
      else if(432>=menor && maior>=437 || 432<=media && media<=437)
      {
		 tecla = 4;
      }
      else if(375>=menor && maior>=380 || 375<=media && media<=380)
      {
		 tecla = 5;
      }
      else if(502>=menor && maior>=510 || 504<=media && media<=510)
      {
		 tecla = 6;
      }
      else if(558>=menor && maior>=566 || 558<=media && media<=566)
      {
		 tecla = 7;
      }
      else if(468>=menor && maior>=473 || 468<=media && media<=473)
      {
		 tecla = 8;
      }
      else if(687>=menor && maior>=692 || 687<=media && media<692)
      {
		 tecla = 9;
      }
      else if(705>=menor && maior>=712 || 707<=media && media<=712)
      {
		 tecla = 10;
      }
      else if(566>=menor && maior>=571 || 566<=media && media<=571)
      {
		 tecla = 0;
      }
      else if(690>=menor && maior>=695 || 690<media && media<695)
      {
		 tecla = 12;
      }
      else if(900<menor)
      {
		 tecla = 12;
      }
    }
    maior = 0;
    menor = 0;
    media = 0;
    c=0;

  }
}

void txt_ciclo(void)
{
	lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Digite o tempo");
  lcd.setCursor(0,1);
  if(on_off == 0)
  {
  lcd.write("acionada:");
  }
  else if(on_off == 1)
  {
  lcd.write("desacionada:");
   }	
}

void txt_bomba(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Digite o numero");
  lcd.setCursor(0,1);
  lcd.write("da bomba:");	
}

void aconteca(void){
	acionamentos();
	//lcd.clear();
	//lcd.print(((millis()/1000) - rtime_1) == (prtime_1),DEC);
	
}

void acionamentos (void)
{
	if((prtime_1 == 0) || (pstime_1  == 0))
	{
		digitalWrite(LAMP_1, HIGH);
	}
	if((prtime_1 != 0) && (pstime_1 != 0))
	{
		if(((millis()/1000) - rtime_1) == (prtime_1))
		{
			digitalWrite(LAMP_1, HIGH); 
			stime_1 = millis()/1000;
		}
		if(((millis()/1000) - stime_1) == (pstime_1))
		{
			digitalWrite(LAMP_1, LOW);
			rtime_1 = millis()/1000;
		}

	}
	
		if((prtime_2 == 0) || (pstime_2  == 0))
	{
		digitalWrite(LAMP_2, HIGH);
	}
	if((prtime_2 != 0) && (pstime_2 != 0))
	{
		if(((millis()/1000) - rtime_2) == (prtime_2))
		{
			digitalWrite(LAMP_2, HIGH); 
			stime_2 = millis()/1000;
		}
		if(((millis()/1000) - stime_2) == (pstime_2))
		{
			digitalWrite(LAMP_2, LOW);
			rtime_2 = millis()/1000;
		}

	}
	
		if((prtime_3 == 0) || (pstime_3  == 0))
	{
		digitalWrite(LAMP_3, HIGH);
	}
	if((prtime_3 != 0) && (pstime_3 != 0))
	{
		if(((millis()/1000) - rtime_3) == (prtime_3))
		{
			digitalWrite(LAMP_3, HIGH); 
			stime_3 = millis()/1000;
		}
		if(((millis()/1000) - stime_3) == (pstime_3))
		{
			digitalWrite(LAMP_3, LOW);
			rtime_3 = millis()/1000;
		}

	}
	
		if((prtime_4 == 0) || (pstime_4  == 0))
	{
		digitalWrite(LAMP_4, HIGH);
	}
	if((prtime_4 != 0) && (pstime_4 != 0))
	{
		if(((millis()/1000) - rtime_4) == (prtime_4))
		{
			digitalWrite(LAMP_4, HIGH); 
			stime_4 = millis()/1000;
		}
		if(((millis()/1000) - stime_4) == (pstime_4))
		{
			digitalWrite(LAMP_4, LOW);
			rtime_4 = millis()/1000;
		}

	}
	
		if((prtime_5 == 0) || (pstime_5  == 0))
	{
		digitalWrite(LAMP_5, HIGH);
	}
	if((prtime_5 != 0) && (pstime_5 != 0))
	{
		if(((millis()/1000) - rtime_5) == (prtime_5))
		{
			digitalWrite(LAMP_5, HIGH); 
			stime_5 = millis()/1000;
		}
		if(((millis()/1000) - stime_5) == (pstime_5))
		{
			digitalWrite(LAMP_5, LOW);
			rtime_5 = millis()/1000;
		}

	}
	
		if((prtime_6 == 0) || (pstime_6  == 0))
	{
		digitalWrite(LAMP_6, HIGH);
	}
	if((prtime_6 != 0) && (pstime_6 != 0))
	{
		if(((millis()/1000) - rtime_6) == (prtime_6))
		{
			digitalWrite(LAMP_6, HIGH); 
			stime_6 = millis()/1000;
		}
		if(((millis()/1000) - stime_6) == (pstime_6))
		{
			digitalWrite(LAMP_6, LOW);
			rtime_6 = millis()/1000;
		}

	}
	
		if((prtime_7 == 0) || (pstime_7  == 0))
	{
		digitalWrite(LAMP_7, HIGH);
	}
	if((prtime_7 != 0) && (pstime_7 != 0))
	{
		if(((millis()/1000) - rtime_7) == (prtime_7))
		{
			digitalWrite(LAMP_7, HIGH); 
			stime_7 = millis()/1000;
		}
		if(((millis()/1000) - stime_7) == (pstime_7))
		{
			digitalWrite(LAMP_7, LOW);
			rtime_7 = millis()/1000;
		}

	}
	
		if((prtime_8 == 0) || (pstime_8  == 0))
	{
		digitalWrite(LAMP_8, HIGH);
	}
	if((prtime_8 != 0) && (pstime_8 != 0))
	{
		if(((millis()/1000) - rtime_8) == (prtime_8))
		{
			digitalWrite(LAMP_8, HIGH); 
			stime_8 = millis()/1000;
		}
		if(((millis()/1000) - stime_8) == (pstime_8))
		{
			digitalWrite(LAMP_8, LOW);
			rtime_8 = millis()/1000;
		}

	}
	
		if((prtime_9 == 0) || (pstime_9  == 0))
	{
		digitalWrite(LAMP_9, HIGH);
	}
	if((prtime_9 != 0) && (pstime_9 != 0))
	{
		if(((millis()/1000) - rtime_9) == (prtime_9))
		{
			digitalWrite(LAMP_9, HIGH); 
			stime_9 = millis()/1000;
		}
		if(((millis()/1000) - stime_9) == (pstime_9))
		{
			digitalWrite(LAMP_9, LOW);
			rtime_9 = millis()/1000;
		}

	}
	
		if((prtime_10 == 0) || (pstime_10  == 0))
	{
		digitalWrite(LAMP_10, HIGH);
	}
	if((prtime_10 != 0) && (pstime_10 != 0))
	{
		if(((millis()/1000) - rtime_10) == (prtime_10))
		{
			digitalWrite(LAMP_10, HIGH); 
			stime_10 = millis()/1000;
		}
		if(((millis()/1000) - stime_10) == (pstime_10))
		{
			digitalWrite(LAMP_10, LOW);
			rtime_10 = millis()/1000;
		}

	}
	
	if((prtime_11 == 0) || (pstime_11  == 0))
	{
		digitalWrite(LAMP_11, HIGH);
	}
	if((prtime_11 != 0) && (pstime_11 != 0))
	{
		if(((millis()/1000) - rtime_11) == (prtime_11))
		{
			digitalWrite(LAMP_11, HIGH); 
			stime_11 = millis()/1000;
		}
		if(((millis()/1000) - stime_11) == (pstime_11))
		{
			digitalWrite(LAMP_11, LOW);
			rtime_11 = millis()/1000;
		}

	}
	
		if((prtime_12 == 0) || (pstime_12  == 0))
	{
		digitalWrite(LAMP_12, HIGH);
	}
	if((prtime_12 != 0) && (pstime_12 != 0))
	{
		if(((millis()/1000) - rtime_12) == (prtime_12))
		{
			digitalWrite(LAMP_12, HIGH); 
			stime_12 = millis()/1000;
		}
		if(((millis()/1000) - stime_12) == (pstime_12))
		{
			digitalWrite(LAMP_12, LOW);
			rtime_12 = millis()/1000;
		}

	}
		
}


void reset(void)
{
  unsigned long int reset_t = 4000000000;
  if(millis() > reset_t)
  {
    asm volatile ("jmp 0x0000");
  }
  
}
