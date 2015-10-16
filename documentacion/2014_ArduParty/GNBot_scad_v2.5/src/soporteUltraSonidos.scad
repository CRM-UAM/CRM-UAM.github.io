
// Increase the resolution of default shapes
$fa = 5; // Minimum angle for fragments [degrees]
$fs = 0.5; // Minimum fragment size [mm]


module soporte(alt,anc){
	refuerzo = 19;
	union() {
		difference(){
			cube([15,27,3]);
			#translate([10-anc,22.5,0])cylinder(r=2,h=30,center=true);
		}
		intersection() {
			cube([15,refuerzo,refuerzo]);
			translate([0,-refuerzo,0]) rotate([-45,0,0]) cube([15,refuerzo*sqrt(2),refuerzo*sqrt(2)]);
		}
		cube([15,5,alt]);
	}
}

module soporteUltraSonidos(altura,anchura){

difference(){
union(){
	//soporte(alt=altura,anc=0);
	difference(){	
		translate([anchura,0,0])soporte(alt=altura,anc=3);
		#translate([45,10,63])rotate([90,0,0])cylinder(r=8,h=20);
	}
}
for(i=[0:10:50]){
if(i<30 || i>=40){
translate([5+0,5,altura-5-i])rotate([90,0,0])cylinder(r=1.8,h=20,center=true);
translate([5+50,5,altura-5-i])rotate([90,0,0])cylinder(r=1.8,h=20,center=true);
}
}
}
}
soporteUltraSonidos(altura=100,anchura=45);
