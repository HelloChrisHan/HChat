
//玩家原型对象
function Player(){

    this.myLives=3;
    this.myInvTime=0;
    this.myImage=new Image();

    this.myPosX=275;
    this.myPosY=50;

    this.myVelX=0;
    this.myVelY=0;
    this.myVelMax=16;
    this.myVel=5;

    this.myAccX=0;
    this.myAccY=0;
    this.myAcc=3;
    this.myDec=1;

    this.myLeft=0;
    this.myRight=0;
    this.myUp=0;
    this.myDown=0;

    this.myWidth=50;
    this.myHeight=50;
}


Player.prototype.init=function(){
    this.myLives=3;
    this.myInvTime=50;
    this.myImage=document.getElementById("shipimg");

    this.myPosX=275;
    this.myPosY=50;

    this.myVelX=0;
    this.myVelY=0;
    this.myVelMax=16;
    this.myVel=5;

    this.myAccX=0;
    this.myAccY=0;
    this.myAcc=3;
    this.myDec=1;

    this.myLeft=0;
    this.myRight=0;
    this.myUp=0;
    this.myDown=0;
}


Player.prototype.update=function(){

    this.myAccX=this.myRight-this.myLeft;
    this.myAccY=this.myDown-this.myUp;

    this.myVelX+=this.myAcc*this.myAccX;
    this.myVelY+=this.myAcc*this.myAccY;

    if(this.myVelX>0)
        this.myVelX-=this.myDec;
    if(this.myVelX<0)
        this.myVelX+=this.myDec;
    if(this.myVelY>0)
        this.myVelY-=this.myDec;
    if(this.myVelY<0)
        this.myVelY+=this.myDec;

    if(this.myVelX>this.myVelMax)
        this.myVelX=this.myVelMax;
    if(this.myVelX<-this.myVelMax)
        this.myVelX=-this.myVelMax;
    if(this.myVelY>this.myVelMax)
        this.myVelY=this.myVelMax;
    if(this.myVelY<-this.myVelMax)
        this.myVelY=-this.myVelMax;
        
    this.myPosX+=this.myVelX;
    this.myPosY+=this.myVelY;

    if(this.myPosX<0)
        this.myPosX=0;
    if(this.myPosX+this.myWidth>600)
        this.myPosX=600-this.myWidth;
    if(this.myPosY<0)
        this.myPosY=0;
    if(this.myPosY+this.myHeight>700)
        this.myPosY=700-this.myHeight;
}

Player.prototype.render=function(ctx){
    if(this.myRight-this.myLeft>0)
        this.myImage=document.getElementById("shipright");
    if(this.myRight-this.myLeft==0)
        this.myImage=document.getElementById("shipimg");
    if(this.myRight-this.myLeft<0)
        this.myImage=document.getElementById("shipleft");

    if(this.myInvTime==0)
        ctx.drawImage(this.myImage,this.myPosX,this.myPosY,this.myWidth,this.myHeight);
    else if((Math.floor(this.myInvTime/5))%2==0)
        ctx.drawImage(this.myImage,this.myPosX,this.myPosY,this.myWidth,this.myHeight);
}