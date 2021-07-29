%% 生成正弦查找表 (LUT)
nbit = 11; % 相位累加器精度，见分析
table_len = 2 ^ nbit;
% 四分之一个周期
sinetable = sin(2*pi*(0:table_len/4)./table_len);
%sinetable = sin(2*pi*(0:table_len-1)./table_len);

%% 转换成DAC输入数据，12位 uint16_t
% 满量程 0~3.3V，输出 0.6~2.6V，偏置1.6V
Vpp = 2;
% offset = (2^12)*(1.6/3.3);  % 查找表本身可加可不加偏置，与单片机程序一致即可
sinetable_dac = round(sinetable*(2^12) * (Vpp / 3.3) / 2);

%% 输出到文件
arr_len = table_len/4;
fp = fopen('sin_lut.c', 'w');
fprintf(fp, ['const int sinelut_' num2str(arr_len) '[] =\n{']);
for i = 1:1:arr_len
    if mod(i, 16) == 1
        fprintf(fp, '\n  ');
    end
    fprintf(fp, '%d, ', sinetable_dac(i));
end
fprintf(fp, '\n};');
fclose(fp);

%% 测试代码
a = ones(1, 2048);
for i = 1:1:2048
    a(i) = get_lut_data(sinetable_dac, offset, i);
end
plot(a)
grid on

function data = get_lut_data(sinetable_dac, offset, acc)
  if acc < 513
    data = sinetable_dac(acc);
  elseif acc == 513
    data = sinetable_dac(acc);
  elseif 514 <= acc && acc <= 1025
    data = sinetable_dac(1026 - acc);
  elseif 1026 <= acc && acc <= 1536
    data = -sinetable_dac(acc - 1025);
  elseif acc == 1537
    data = -sinetable_dac(512);
  elseif 1538 <= acc && acc <= 2048
    data = -sinetable_dac(2050 - acc);
  end
end
