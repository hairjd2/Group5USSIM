clear;
close all;
wave = importdata('wave.txt', '\t', 0);

plot(wave(:, 1), wave(:, 2), 'r', LineWidth=1);