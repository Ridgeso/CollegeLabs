clear; clc; close all;

im = double(imread('kaczki.jpg')) / 255.0;
im = rgb2gray(im);

imshow(im);

% progujemy bu uzyskac tylko nasze kaczki
t = graythresh(im);

figure;

% binaryzujemy by otrzymac tylko ich konktury
tim = im;
tim =  ~imbinarize(tim, t);

% zamykamy powstale dziury i wygladzamy koncowy obraz
tim = imclose(tim, ones(12));
tim = medfilt2(tim, [10, 10]);

imshow(tim);

% MORFOLOGIA

figure; 
w = 2; h = 2;

tim2 = bwmorph(tim, 'remove');
% Inne: 'close', 'open', 'erode', 'dilote', 'fill', 'cleon', 'median',
% 'remove'

subplot(w, h, 1);
imshow(tim2);

% tworzymy szkielet kaczek, ktory jest zbiorem punktow rowno oddalonych od
% krawedzi, taki szkielet mozna przywrocic do pierwotnej postaci przy
% urzyciu np. erode
skel = bwmorph(tim, 'skel', 50);

subplot(w, h, 2);
imshow(skel);

% pozostawia to jasne tylko te piksele ktory byly na krawedziach lini
skel2 = bwmorph(skel, 'endpoints');
subplot(w, h, 3);
imshow(skel2);

% pozostawia to jasne tylko te piksele ktory byly na polaczeniach lini
skel3 = bwmorph(skel, 'branchpoints');
subplot(w, h, 4);
imshow(skel3);

figure;

% robi erozje wzgledem glownego punktu calego obiektu
shr = bwmorph(tim, 'shrink', inf);

subplot(w, h, 1);
imshow(shr);

% robi redukuje az do pojedynczej lini
thin = bwmorph(tim, 'thin', inf);

subplot(w, h, 2);
imshow(thin);

% Liczba eulera w operacjah morfologicznych (czy ilosc obiektow jest
% zachowana)

% przeciwienstwo 'thin', dzieli nam obraz na sektory gdzie mamy pewnosc ze
% w kazdym sektorze jest jeden obiekt
thic = bwmorph(tim, 'thicken', inf);

subplot(w, h, 3);
imshow(thic);

% tworzymy macierz gdzie 0=tlo, 1...inf=obiekt o nr n
l = bwlabel(tim);

subplot(w, h, 4);
imshow(label2rgb(l));

figure;
% ta operacja przechowuje tylko kaczke nr n;
subplot(w, h, 1);
imshow((l == 1) .* im);
subplot(w, h, 2);
imshow((l == 2) .* im);
subplot(w, h, 3);
imshow((l == 3) .* im);

subplot(w, h, 4);
% to daje nam ostry obraz kaczki i znowu mozna przeprowadzic tesame
% operacje tylko ostrzej
imshow((bwlabel(thic) == 2) .* im);

figure;

% transformata odleglosciowa
d = bwdist(~tim);
subplot(w, h, 1);
imshow(d, [0, max(d, [], 'all')]);

timk = tim;
timk(:, [1, end]) = 1;
timk([1, end], :) = 1;

d2 = bwdist(timk);

% wyznaczamy obszary na okolo obiektow
l2 = watershed(d2);

subplot(w, h, 2);
imshow(l2, [0, max(l2, [], 'all')]);

d3 = bwdist(timk, 'cityblock');
d3 = watershed(d3);
% jest jeszcze 'chessboard', 'euclidean'

subplot(w, h, 3);
imshow(d3, [0, max(d3, [], 'all')]);

d3 = bwdist(timk, 'chessboard');
d3 = watershed(d3);
subplot(w, h, 4);
imshow(d3, [0, max(d3, [], 'all')]);


