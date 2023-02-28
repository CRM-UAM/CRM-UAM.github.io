// (C) CarlosGS 2023

projection(cut=true)
translate([0,0,-8])
difference(){
    union() {
    import("N31.stl", convexity=3);
    cylinder(r=10,h=40,center=true);
    }
    scale(0.9) translate([-9,0,7])
        linear_extrude(30) import("crm_logo_pegatina.dxf");
}
