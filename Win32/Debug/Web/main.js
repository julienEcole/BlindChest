function refresh() 
{       var unique = new Date();
        document.images.monEchiquier.src = "Position.jpg&unique=" + unique.getTime(); // ou via getElementById
}
window.onload = function ()
{       setInterval("refresh()", 500);
}

