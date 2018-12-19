close all;
M = csvread('Data.csv',1,0);
X=M(:,1);

%% Grafico maximum tree height (mean)
figure(1);
Y=M(:,2);
D=[log(X),1+0*X];
w=pinv(D)*Y
plot(log10(X),Y,'b',log10(X),D*w,'k');
title('Grafico maximum tree height (mean)')
%Y_mod=log(X)+15

%plot(log10(X),Y);




%plot(X,Y_mod,'r');



%% Grafico number of leaves (mean)
figure(2);
Y=M(:,3);

D=[X,1+0*X];
w=pinv(D)*Y
plot(X,Y,'b',X,D*w,'k');

title('Grafico number of leaves (mean)')

%% Grafico calls on hit (mean)
figure(3);
Y=M(:,4);
D=[log(X),1+0*X];
w=pinv(D)*Y
plot(log10(X),Y,'b',log10(X),D*w,'k');
title('Grafico calls on hit (mean)')

%% Grafico calls on miss (mean)
figure(4);
Y=M(:,5);
D=[log(X),1+0*X];
w=pinv(D)*Y
plot(log10(X),Y,'b',log10(X),D*w,'k');
title('Grafico calls on miss (mean)')

