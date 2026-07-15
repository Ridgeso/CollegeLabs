% x = linspace(-5, 5);
% y = x;
% [X, Y] = meshgrid(x, y);
% 
% z = (sin(X).*cos(Y)) ./(X.^2 + Y.^2 + 1);
% surf(X, Y, z);

% syms a b c x
% 
% y = a*x^2 + b*x + c;
% 
% a = 5;
% b = 2;
% c = 1;
% 
% delta = b^2 - 4*a*c;
% delta = sqrt(delta);
% 
% x1 = (-b-delta)/(2*a);
% x2 = (-b+delta)/(2*a);
% 
% disp("LOL");
% disp(x1);
% disp(x2);

% clear; clc; close all;
% 
% a = [1, 2, 3; 4, 5, 6];
% b = [7, 8, 9; 10, 11, 12];
% 
% val1 = a + b;
% val2 = a * b' / 12;
% val3 = a .* b;
% 
% 
% x = 0 : 0.1 : pi;
% y = sin(x);
% plot(x, y);
% 
% 
% 
% startpos = [0, 0];
% endpos = [12, 6];
% 
% len = length(endpos - startpos);
% if len > 0
%     
% end
% 
% for i = 1 : 5
%     
% end

uklad = [1, 2, 3, 4;
        1, 4, 9, 16;
       25, 16, 7, 3;
       8, 5, 3, 13];
rozw = [1, 2, 3, 4];
x = 1 : 4;
x(:) = 0;

detuklad = det(uklad);
for i = 1 : 4
    ukladxi = uklad;
    ukladxi(:, i) = rozw;
    x(i) = det(ukladxi) / detuklad;
end

disp(x);

x = uklad^-1 * rozw';
disp(x');

