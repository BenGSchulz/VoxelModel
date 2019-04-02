// Originally provided by DU Computer Science Department
// Modified by Ben Schulz

var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(
	75, window.innerWidth / window.innerHeight, 0.1, 1000 );

var renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

bits = [];
var inputString = window.location.hash.substring(1);
if(inputString){
	var inputAsBigInt = BigInteger(inputString)
	
	for(var i = 0; i < 64; i++){
		if(inputAsBigInt.remainder(2).compare(BigInteger(1)) == 0){
			bits[i] = true;
		}
		inputAsBigInt = inputAsBigInt.divide(2);
	}
} else {
	for(var i = 0; i < 64; i++){
		if(Math.random() > .75){
			bits[i] = true;
		}
	}
}

for(var x = 0; x < 4; x++){
	for(var y = 0; y < 4; y++){
		for(var z = 0; z < 4; z++){
			if(bits[x*16 + y*4 + z]){
				var geometry = new THREE.BoxGeometry( .9, .9, .9 );
				var material = new THREE.MeshPhongMaterial( { color: new THREE.Color( x/3, y/3, z/3 ) });
				var cube = new THREE.Mesh( geometry, material );
				cube.position.copy(new THREE.Vector3(x, y, z));
				cube.updateMatrix();
				scene.add( cube );
			}
		}
	}
}

light1 = new THREE.PointLight( 0xff0040, 2, 50 );
light1.position.set( 10, 10, 10 );
scene.add( light1 );
light2 = new THREE.PointLight( 0x0040ff, 2, 50 );
light2.position.set( -10, -10, 10 );
scene.add( light2 );
light3 = new THREE.PointLight( 0x80ff80, 2, 50 );
light3.position.set( 10, 10, -10 );
scene.add( light3 );
light4 = new THREE.PointLight( 0xffaa00, 2, 50 );
light4.position.set( -10, -10, -10 );
scene.add( light4 );

var angle = 0;
var render = function () {
	requestAnimationFrame( render );

	xy = Math.cos(angle)
	z = Math.sin(angle)
	angle += .01;
	camera.lookAt(new THREE.Vector3(1, 1, 1));
	var r = 15;
	camera.position.copy(new THREE.Vector3(r*xy, r*xy, r*z));
	camera.updateMatrix();

	renderer.render(scene, camera);
};

render();
