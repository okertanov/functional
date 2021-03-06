//
// Helium
//

module Helium() {
    nRad = 10;
    eRad = 5;
    oRad = 25;
    fn= 100;

    union()
    {
        union()
        {
            translate([0, 1, 0])
                color("Silver")
                sphere(r = nRad, center=true, $fn = fn);
            translate([1, 0, 1])
                color("IndianRed")
                sphere(r = nRad, center=true, $fn = fn);
            translate([0, -1, 0])
                color("Silver")
                    sphere(r = nRad, center=true, $fn = fn);
            translate([-1, 0, -1])
                color("IndianRed")
                    sphere(r = nRad, center=true, $fn = fn);
        }
        union()
        {
            color("Silver")
                linear_extrude(height = 0.1)
                    difference()
                    {
                        circle(r = oRad, $fn = fn, center = true);
                        circle(r = oRad-0.1, $fn = fn, center = true);
                    }
        }
        rotate(a=[90,90,0])
        union()
        {
            color("Silver")
                linear_extrude(height = 0.1)
                    difference()
                    {
                        circle(r = oRad, $fn = fn, center = true);
                        circle(r = oRad-0.1, $fn = fn, center = true);
                    }
        }
        union()
        {
            translate([0, 0, oRad])
                color("DeepSkyBlue")
                    sphere(r = eRad, $fn = 12);
        }
        union()
        {
            translate([0, oRad, 0])
                color("DeepSkyBlue")
                    sphere(r = eRad, $fn = 12);
        }
    }
}

Helium();

