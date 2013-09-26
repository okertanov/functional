(function()
{

$(function()
{
    console.log( "App loading complete." );

    var camera, scene, renderer;
    var geometry, material;

    init();
    animate();
});

function init()
{
    const SegmentSize = 1;

    camera = new THREE.PerspectiveCamera( 125, window.innerWidth / window.innerHeight, 0.1, 1000 );
    camera.position.z = 1000;

    scene = new THREE.Scene();

    var mesh1 = new THREE.Mesh(
            new THREE.PlaneGeometry(100, 100),
            new THREE.MeshBasicMaterial({ color: 0xAA0000, wireframe: true })
            );
    var mesh2 = new THREE.Mesh(
            new THREE.PlaneGeometry(200, 200),
            new THREE.MeshBasicMaterial({ color: 0x00AA00, wireframe: true })
            );
    var mesh3 = new THREE.Mesh(
            new THREE.PlaneGeometry(800, 800),
            new THREE.MeshBasicMaterial({ color: 0x0000AA, wireframe: true })
            );
    var mesh4 = new THREE.Mesh(
            new THREE.PlaneGeometry(3200, 3200),
            new THREE.MeshBasicMaterial({ color: 0xAAAA00, wireframe: true })
            );
    scene.add( mesh1 );
    scene.add( mesh2 );
    scene.add( mesh3 );
    scene.add( mesh4 );

    renderer = new THREE.WebGLRenderer();
    renderer.setSize( window.innerWidth, window.innerHeight );

    document.body.appendChild( renderer.domElement );
}

function animate()
{
    renderer.render( scene, camera );

    requestAnimationFrame( animate );
}

}
());
