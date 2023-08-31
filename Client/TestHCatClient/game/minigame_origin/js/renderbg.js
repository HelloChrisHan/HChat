var bgimg=document.getElementById("background");

var bgy=0;

function rendbg(ctx){
    bgy-=ship.myVel;
    if(bgy<=-256)
        bgy+=256;
    ctx.fillStyle="#330099";
    ctx.fillRect(0,0,600,700);
    for(var j=0;j<4;j++){
        for(var i=0;i<3;i++){
            ctx.drawImage(bgimg,256*i,bgy+256*j,256,256);
        }
    }
}