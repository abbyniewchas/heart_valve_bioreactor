function dVdt = bladder_diffeqn(t,V)
    
    rho = 1;
    g = 9.8;
    h = 0.6096/2;
    r = 0.006;
    eta = 8.9e-4;
    l = 0.6096;
    Kb = 0.0076;
    A = 4.0079e-05;
    
    dVdt = (pi * (rho*g*h - (Kb*V/(A^2))) * r^4) / (8 * eta * l);
    
end

