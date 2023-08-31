

function downkey(e){
    e.preventDefault();
    start=1;
    switch(e.keyCode){
        case 37:
            ship.myLeft=1; break;
        case 39:
            ship.myRight=1; break;
        case 38:
            ship.myUp=1; break;
        case 40:
            ship.myDown=1; break;
    }
}



function upkey(e){
    e.preventDefault();
    start=1;
    switch(e.keyCode){
        case 37:
            ship.myLeft=0; break;
        case 39:
            ship.myRight=0; break;
        case 38:
            ship.myUp=0; break;
        case 40:
            ship.myDown=0; break;
    }
}