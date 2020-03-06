% Read in data collected to get an approximated spring constant for the
% current bladder

% Data was collected by raising fluid reservoir to varying heights and
% measuring the corresponding *peak* displacement in the bladder. The force
% applied by the water pressure over the bladder area must be equal to the
% reactionary force that the bladder applies back on the water

% Ted Lutkus

% Load data
data = readmatrix("bladder_constant_experiment.csv");
data = data./1000; % [mm] -> [m]
h = data(:,1) - data(1,1);
bladder_disp = data(:,2) - data(1,2);

%{
Model being used:

P_bladder = rho * g * h
F_bladder = P_bladder * A

F_bladder = k * bladder_disp
((rho*g*h) * A) = k * bladder_disp

%}

% Calculate F_bladder
rho = 1;
g = 9.8;
% calculate area as area of two semicircles with a rectangle between
% r = 0.045, w = 0.09, l = 0.07
A = pi*(0.045^2) * (0.09 * 0.07); % measurements of 
F_bladder = rho * g * h * A;

% Estimate linear and nonlinear fit
lin_fit = fitlm(bladder_disp, F_bladder)
nlin_fit = polyfit(bladder_disp, F_bladder, 2);

disp_vec = 0:0.0001:max(bladder_disp);
lin_vec = lin_fit.Coefficients{2,1} * disp_vec + lin_fit.Coefficients{1,1};
nlin_vec = nlin_fit(1) * (disp_vec.^2) + nlin_fit(2) * disp_vec + nlin_fit(3);

% Plot results
figure;
plot(bladder_disp, F_bladder, 'o', 'LineWidth', 2);
hold on;
plot(disp_vec, lin_vec);
hold on;
plot(disp_vec, nlin_vec);
xlabel('Bladder Displacement [m]')
ylabel('Bladder Force [N]')
legend({'Data', 'Linear Fit', 'Nonlinear Fit'}, 'Location', 'southeast')

