clear; clc; close all;

rgbim = double(imread('ptaki.jpg')) / 255.0;
im = rgb2gray(rgbim);

imshow(im);
w = 2; h = 2;

figure;

rbim =  imbinarize(rgbim(:,:,1));
gbim =  imbinarize(rgbim(:,:,2));
bbim =  imbinarize(rgbim(:,:,3));

bim = rbim |~ bbim;
bim = imopen(bim, ones(7));
bim = imclose(bim, ones(7));
l = bwlabel(bim);

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

subplot(1, 2, 1);
imshow(l == fn);

% Zeby sie jej pozbyc robimy szystko po kolei
m = mean(M);
S = std(M);
out = abs(M - m) ./ S;
t = 1.8;
idx = out > t;

idx = sum(idx, 2) > 2;

outidx = find(idx);

M(outidx, :) = [];
l(l == outidx) = 0;
bim = l > 0;

subplot(1, 2, 2);
imshow(bim);

%%%%%% nowy obraz
