
function iscollision(ship,rock){
   var AX1=ship.myPosX;
   var AY1=ship.myPosY;
   var AX2=ship.myPosX+ship.myWidth;
   var AY2=ship.myPosY+ship.myHeight;
   var BX1=rock.myPosX;
   var BY1=rock.myPosY;
   var BX2=rock.myPosX+rock.myWidth;
   var BY2=rock.myPosY+rock.myHeight;
   return collision(AX1+15,AY1,AX2-15,AY2,BX1,BY1+rock.myWidth/2,BX2,BY2);
}

function collision(AX1,AY1,AX2,AY2,BX1,BY1,BX2,BY2){
   if (AX1<BX1){
      if (AX2<BX1)
         return false;
      else{
         if (AY1<BY1){
            if (AY2<BY1)
               return false;
            else
               return true;
         }
         else{
            if (AY1>BY2)
               return false;
            else
               return true;
         }
      }
   }
   else{
      if (AX1>BX2)
         return false;
      else{
         if (AY1<BY1){
           if (AY2<BY1)
              return false;
           else
              return true;
         }
         else{
            if (AY1>BY2)
               return false;
           else
              return true;
         }
      }
   }
   return false;
}
