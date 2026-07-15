clear; clc; close all;

rim = double(imread('opera.jpg')) / 255.0;
im = rgb2gray(rim);

figure;
w = 3; h = 2;

subplot(w, h, 1);
imshow(im);

fim = fft2(im);

A = abs(fim);
phi = angle(fim);

subplot(w, h, 2);
imshow(A, [0, max(A, [], 'all')]);

max(A, [], 'all')

subplot(w, h, 3);
imshow(log(A), [0, log(max(A, [], 'all'))]);

subplot(w, h, 4);
sA = fftshift(A);
imshow(log(sA), [0, log(max(sA, [], 'all'))]);


z = A .* exp(1i * phi);
ifim = ifft2(z);

subplot(w, h, 5);
imshow(abs(ifim));

cA = A;
cA(5, 7) = 10^5;
z = cA .* exp(1i * phi);
ifim = ifft2(z);

subplot(w, h, 6);
imshow(abs(ifim));

figure;

subplot(w, h, 1);
imshow(phi, [-pi, pi]);


[iw, ih] = size(im);
f = ones(7) / 7^2;
ff = fft2(f, iw, ih);
fA = abs(ff);
fphi = angle(ff);

subplot(w, h, 2);
imshow(log(fA), [min(log(fA), [], 'all'), max(log(fA), [], 'all')]);

subplot(w, h, 3);
imshow(fphi, [-pi, pi]);


nfA = A .* fA;
z = nfA .* exp(1i * phi);
ifim = ifft2(z);
subplot(w, h, 4);
imshow(abs(ifim));

m = zeros(iw, ih);
m(1 : 200, 1 : 200) = 1;
m(end - 200 : end, end - 200 : end) = 1;
m(1 : 200, end - 200 : end) = 1;
m (end - 200, 1 : 200) = 1;

nfA = A .* m;
z = nfA .* exp(1i * phi);
ifim = ifft2(z);
subplot(w, h, 5);
imshow(abs(ifim));

% pause;
% close all;