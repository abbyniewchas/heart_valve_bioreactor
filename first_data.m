data = readmatrix('piston_bladder_test1.csv');
data1 = readmatrix('piston_bladder_test2.csv');
data2 = readmatrix('piston_bladder_test3.csv');

figure;
yyaxis left;
plot(data1(:,1)/1000, data1(:,2), '-x');

yyaxis right;
plot(data1(:,1)/1000, data1(:,3), '-o');
legend({'pump paddle position', 'comp chamber pressure 2'});

figure;
plot(data(:,1), (data(:,3)*0.750062) - 766, '-o');
hold on
plot(data1(:,1), (data1(:,3)*0.750062) - 766, '-o');
hold on
plot(data2(:,1), (data2(:,3)*0.750062) - 766, '-o');
legend({'comp chamber pressure 1', 'comp chamber pressure 2', 'comp chamber pressure 3'});

% legend({'pump paddle position', 'comp chamber pressure 1', 'comp chamber pressure 2', 'comp chamber pressure 3'});
xlabel('time [ms]');
ylabel('pressure [mmHg]');