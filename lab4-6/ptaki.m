clear; clc; close all;

rgbim = double(imread('ptaki.jpg')) / 255.0;
im = rgb2gray(rgbim);

imshow(im);
w = 2; h = 2;

figure;

% problem polega ze tlo jest gradnienten przez co ciezko jest przeprowadzic
% binaryzacje, musimy przeanalizowac histogramy by wiedziec na ktorych
% kanalach to zrobic
redChanel = rgbim;
greenChanel = rgbim;
blueChanel = rgbim;
redChanel(:, :, [2, 3]) = 0;
greenChanel(:, :, [1, 3]) = 0;
blueChanel(:, :, [1, 2]) = 0;

subplot(3, 2, 1);
imshow(redChanel);
subplot(3, 2, 2);
histogram(rgbim(:,:,1));
subplot(3, 2, 3);
imshow(greenChanel);
subplot(3, 2, 4);
histogram(rgbim(:,:,2));
subplot(3, 2, 5);
imshow(blueChanel);
subplot(3, 2, 6);
histogram(rgbim(:,:,3));

figure;

t = graythresh(im) - 0.15;
rbim =  imbinarize(rgbim(:,:,1));
gbim =  imbinarize(rgbim(:,:,2));
bbim =  imbinarize(rgbim(:,:,3));

% przeprowadzamy binarnego ora na liczbach by binaryzacja byla mozliwa
bim = rbim |~ bbim;

subplot(1, 3, 1);
imshow(rbim);
subplot(1, 3, 2);
imshow(gbim);
subplot(1, 3, 3);
imshow(bbim);

figure;

bim = imopen(bim, ones(7));
bim = imclose(bim, ones(7));
%bim = bwmorph(bim, 'erode', 20);
imshow(bim);

% tworzymy strukture 'a' ktora jest wszystkimi tymi obiektami ktore naleza
% do figury nr 4
l = bwlabel(bim);
a = regionprops(l == 4, 'all');

% najmniejszy prostokat zawierajacy w sobie figure
a.BoundingBox;
% najdluzsza os figury
a.MaxFeretAngle;
% centrum masy obiektu
a.Centroid;
% kat miedzy osia glowna a osia ukladu
a.Orientation;
% wszystkie 'Convex...' 
a.ConvexArea;
% jaka czesc przestrzeni wypelnia obiekt w boundingboxie
a.Solidity;
% Obwod
a.Perimeter;
% Osie fereta czyli dlugosc i wysokosc figury na osi ukladu

figure;
subplot(1, 2, 1);
imshow(a.Image);

% tworzymy stosunek pola kola do jego obwodu, by okreslic jak bardzo kragla
% jest kaczka, pole kola i jego owbod sa rowne tym co kaczki
Sf = sqrt(a.Area / pi);
Lf = a.Perimeter / (2 * pi);
% circularity coefficient
S = Sf / Lf;
% wspolczynnik malinowskiego
m = Lf / Sf - 1;
% wspolczynnik Bloir Bliss
% w. Danielssona
% w. haralicka

fim = {@AO5RBlairBliss, @AO5RCircularityL, @AO5RCircularityS, @AO5RDanielsson, @AO5RFeret, @AO5RHaralick, @AO5RMalinowska, @AO5RShape};

fm = length(fim);
fn = max(l, [], 'all');
M = zeros(fn, fm);

% Tworzymy macierz naszych wspol. dla kazdej gesi
for i = 1:fn
    for j = 1:fm
        M(i, j) = fim{j}(l == i);
    end
end

subplot(1, 2, 2);
imshow(l == fn);
