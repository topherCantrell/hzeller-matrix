var matrix = require('./build/Release/matrix');

function draw(red, green, blue) {

	for (var x = 0; x < 32; x++)
		for (var y = 0; y < 32; y++)
			matrix.setPixel(x, y, red, green, blue);
	
	matrix.refresh();
}

matrix.configure(32, 32);
matrix.drawPixel(5, 5, 255, 255, 255);
matrix.update();

setTimeout(function(){
	//matrix.stop();	
}, 3000);


