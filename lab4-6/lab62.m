clear; clc; close all;

im = rgb2gray(double(imread('ptaki2.jpg')) / 255.0);
im2 = double(imread('ptaki.jpg')) / 255.0;

figure;

bim = ~imbinarize(im);
bim = imopen(bim, ones(7));
bim = imclose(bim, ones(7));
l = bwlabel(bim);

rbim =  imbinarize(im2(:,:,1));
bbim =  imbinarize(im2(:,:,3));
bim2 = rbim |~ bbim;
bim2 = imopen(bim2, ones(7));
bim2 = imclose(bim2, ones(7));
l2 = bwlabel(bim2);

% usuwanie obiektow po ich polu
t = 750;
for i=1 : max(l, [], 'all')
    a = regionprops(l == i, 'Area');
    if a.Area < t
        l(l == i) = 0;
    end
end
for i=1 : max(l2, [], 'all')
    a = regionprops(l2 == i, 'Area');
    if a.Area < t
        l2(l2 == i) = 0;
    end
end

bim = l > 0;
l = bwlabel(bim);
bim2 = l2 > 0;
l2 = bwlabel(bim2);

fim = {@AO5RBlairBliss, @AO5RCircularityL, @AO5RCircularityS, @AO5RDanielsson, @AO5RFeret, @AO5RHaralick, @AO5RMalinowska, @AO5RShape};
fm = length(fim);

fn = max(l, [], 'all');
M = zeros(fm, fn);
imshow(l);
fn2 = max(l2, [], 'all');
M2 = zeros(fm, fn2);

% Tworzymy macierz naszych wspol. dla kazdej gesi
for i = 1:fn
    for j = 1:fm
        M(i, j) = fim{j}(l == i);
    end
end
for i = 1:fn2
    for j = 1:fm
        M2(i, j) = fim{j}(l2 == i);
    end
end

n1 = max(l, [], 'all');
n2 = max(l2, [], 'all');

uin = [M(1 : end - 2, :), M2(1 : end - 2, :)]';
uout = [repmat([1; 0], 1, n1 - 2), repmat([0; 1], 1, n2 - 2)];

tin = [M(end - 1 : end, :), M2(end - 1 : end, :)]';
tout = [1, 1, 0, 0; 0, 0 1, 1];

nn = feedforwardnet;
mm = train(nn, uin, uout);

nn(M(2,:)');
round(nn(tim));

% properswithcode
