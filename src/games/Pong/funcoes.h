/*//-----------------BARRA BOTOES-----------------

    //baixo
    if(digitalRead(botao_azul) == 0){ //se o botao azul for apertado 
        if(coordY_B2+(square_Height) <= 230){ 
            coordY_B2 += 10;
            /*100 + 30 <= 240? Sim
            
            190 maximo
            
            
        }
    
    }
    else if(digitalRead(botao_amarelo) == 0){ //se o botao azul for apertado 
        coordY_B2 -= 10;
        if(coordY_B2+(square_Height) == 50){ 
            coordY_B2 += 10;
        
        }

            
        
    
    }
    Serial.println(coordY_B2);*/