
var ship= new Player();
var rocks=new Array();

var rocknum=8;

var score=0;
var timecount=0;

var canvas=document.getElementById("gamezone");
var ctx=canvas.getContext("2d");

var start=0;

function initgame(){
    ship.init();
    for(var i=0;i<rocknum;i++){
        rocks[i]=new Rock();
        rocks[i].init();
    }
}
initgame();

document.addEventListener("keydown",downkey);
document.addEventListener("keyup",upkey);

function startgame(){
    ctx.clearRect(0,0,600,700);

    rendbg(ctx);
    ship.render(ctx);
    for(var i=0;i<rocknum;i++){
        rocks[i].render(ctx);
    }
    ctx.fillStyle="#FFFFFF";
    ctx.font="40px Georgia";
    ctx.fillText("Press any key to start",120,310);
    ctx.fillText("Use arrow keys to move",120,390);
    waitstart();
}

function waitstart(){
    if(start==0){
        setTimeout(() => {
            requestAnimationFrame(waitstart)
        }, 1000/60);
    }
    else
        ingame();
}

function ingame(){
    timecount++;
    if(timecount===100)
        timecount=0;
    if(ship.myVel<5&&timecount%10==0)
        ship.myVel++;
    if(ship.myVel<15&&timecount==0)
        ship.myVel+=1;
    if(ship.myInvTime>0)
        ship.myInvTime--;

    
    score+=ship.myVel/10;

    ship.update();
    for(var i=0;i<rocknum;i++){
        rocks[i].update();

        if(iscollision(ship,rocks[i])&&ship.myInvTime==0){
            ship.myLives-=1;
            ship.myInvTime=50;
            ship.myVel=0;
        }
    }
    

    ctx.clearRect(0,0,600,700);

    rendbg(ctx);
    ship.render(ctx);
    for(var i=0;i<rocknum;i++){
        rocks[i].render(ctx);
    }
    ctx.fillStyle="#FFFFFF";
    ctx.font="20px Georgia";
    ctx.fillText("Lives: "+ship.myLives+"    Score: "+Math.floor(score),10,20);

    if(ship.myLives>0){
        setTimeout(() => {
            requestAnimationFrame(ingame)
        }, 1000/60);
    }
    else
        gameover();
}


function gameover(){
    ctx.clearRect(0,0,600,700);

    rendbg(ctx);
    ship.render(ctx);
    for(var i=0;i<rocknum;i++){
        rocks[i].render(ctx);
    }
    ctx.fillStyle="#FFFFFF";
    ctx.font="40px Georgia";
    ctx.fillText("GAME OVER",160,310);
    ctx.fillText("Your Score is: "+Math.floor(score),140,390);
}

startgame();
