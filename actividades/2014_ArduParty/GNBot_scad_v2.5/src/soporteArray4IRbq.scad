
// Increase the resolution of default shapes
$fa = 5; // Minimum angle for fragments [degrees]
$fs = 0.5; // Minimum fragment size [mm]

module IR(){
#import("Sensor_Ir.stl");
translate([-1.5,11,0])cylinder(h=15,r=1.7,center=true);
translate([15.1,0,0])cylinder(h=15,r=1.7,center=true);
#translate([-13,-4.1,-20])cube([23,9.7,50]);
}
module arrayIR(){
IR();
translate([0,19,0])IR();
translate([0,38,0])IR();
translate([0,57,0])IR();
}

/*difference(){
translate([-20,-85/2,0])cube([40,85,4]);
translate([0,-60/2,0])arrayIR();
translate([-20,-70/2,-15])cube([15,70,30]);
}


translate([0,-60/2,10])arrayIR();*/
module soporteIRbq(ampTor){
refuerzo = 8;
difference(){
	union(){
		translate([-50,-15,-2])cube([2,90,20]);
		minkowski(){		
			translate([-45,-15,-2])cube([65,90,2]);
			cylinder(r=4, h=0.5);
		}
		translate([-50,-15+90,-2]) rotate([0,0,-90])
			intersection() {
				cube([90,refuerzo,refuerzo]);
				translate([0,-refuerzo,0]) rotate([-45,0,0]) cube([90,refuerzo*sqrt(2),refuerzo*sqrt(2)]);
			}
	}

	translate([6.7,-10,-10])cube([7.6,80,20]);
	translate([1.7,0,0])arrayIR();
	translate([0.2,-8,0])cylinder(h=15,r=1.7,center=true);
	translate([-55,-20,-15])cube([30,30,40]);
for(i=[0:10:20]){	
translate([-45,17+i,-15])cube([20,5,40]);
}
	translate([-55,50,-15])cube([30,30,40]);
	translate([-60,30-ampTor/2,12])rotate([0,90,0])minkowski(){
		cube([7,2,30]);
		cylinder(r=1, h=2);
	}
	translate([-60,30+ampTor/2,12])rotate([0,90,0])minkowski(){
		cube([7,2,30]);
		cylinder(r=1, h=1);
	}
}
}


soporteIRbq(ampTor=20);
