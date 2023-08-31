

function Rock(){

    this.myPosX=0;
    this.myPosY=0;
    this.myImage=new Image();

    this.myWidth=50;
    this.myHeight=50;
}

Rock.prototype.init=function(){
    this.myWidth=Math.floor(Math.random()*40-20)+70;
    this.myHeight=Math.floor(Math.random()*40-20)+70;
    this.myPosX=Math.floor(Math.random()*(600-this.myWidth)+1);
    this.myPosY=Math.floor(Math.random()*900+1)+350;
    if(Math.random()>0.5)
        this.myImage=document.getElementById("rock1");
    else
        this.myImage=document.getElementById("rock2");
}


Rock.prototype.regenerate=function(){
    this.myWidth=Math.floor(Math.random()*40-20)+70;
    this.myHeight=Math.floor(Math.random()*40-20)+70;
    this.myPosX=Math.floor(Math.random()*(600-this.myWidth)+1);
    this.myPosY=Math.floor(Math.random()*350+1)+700;
    if(Math.random()>0.5)
        this.myImage=document.getElementById("rock1");
    else
        this.myImage=document.getElementById("rock2");
}

Rock.prototype.update=function(){
    this.myPosY-=ship.myVel;
    if(this.myPosY+this.myWidth<0)
        this.regenerate();
}

Rock.prototype.render=function(ctx){
    ctx.drawImage(this.myImage,this.myPosX,this.myPosY,this.myWidth,this.myHeight);
}