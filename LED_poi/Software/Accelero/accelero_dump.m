close all;
clear all;
putty=load("putty.log");

Fs=1/(10e-3);
Ts=1/Fs;
start=1;
stop=length(putty);
data=putty(start : stop);
N=length(data)-1;
t=(0:N)*Ts;

data_filt(1)=data(1);
dmin(1)=data_filt(1);
%dmid(1)=data_filt(1);
dmax(1)=data_filt(1);
out_sig(1)=1e3;
decay=50;
filtN=4;
for i = 2:N+1
  data_filt(i)=(data(i)+data_filt(i-1)*(filtN-1))/filtN;
  dmin(i)=min(dmin(i-1)+decay,data_filt(i));
  dmax(i)=max(dmax(i-1)-decay,data_filt(i));
  if(dmin(i)==data_filt(i))
    if(out_sig==8e3)
      disp(i);
    endif
    out_sig(i)=1e3;
  elseif(dmax(i)==data_filt(i))
    out_sig(i)=8e3;
  else
    out_sig(i)=out_sig(i-1);
  endif
  %dmid(i)=(dmin(i)+dmax(i))/2;
endfor

subplot (2, 1, 1);

plot(t,data,'DisplayName',"Raw data");
hold on;
plot(t,data_filt,'DisplayName',"Filtered data");
plot(t,dmin,'DisplayName',"Min");
%plot(t,dmid,'DisplayName',"Mid");
plot(t,dmax,'DisplayName',"Max");
plot(t,out_sig,'DisplayName',"out");
legend();
title('Time domain signal');
xlabel('t (seconds)');
ylabel('Z axis acceleration (in mG)');



subplot (2, 1, 2);

plot(t,(dmax-dmin),'DisplayName',"diff");
hold on;
plot(t,(dmax+dmin)/2,'DisplayName',"avg");
legend();
title('Time domain signal');
xlabel('t (seconds)');
ylabel('Z axis acceleration (in mG)');

##
##fdat=fft(data);
##fdat = abs(fdat/N);
##fdat = fdat(1:N/2+1);
##fdat(2:end-1) = 2*fdat(2:end-1);
##
##fdatf=fft(data_filt);
##fdatf = abs(fdatf/N);
##fdatf = fdatf(1:N/2+1);
##fdatf(2:end-1) = 2*fdatf(2:end-1);
##f = Fs*(0:(N/2))/N;
##
##startF=find(f>0.5,1,'first');
##
##subplot (2, 1, 2);
##semilogx(f(startF:end),fdat(startF:end),'DisplayName',"Raw spectrum");
##hold on;
##semilogx(f(startF:end),fdatf(startF:end),'DisplayName',"Filtered spectrum");
##legend();
##grid;
##title('Spectrum view');
##xlim([f(startF) max(f)]);
##xlabel('f (Hz)');
##ylabel('|FFT(f)|');

