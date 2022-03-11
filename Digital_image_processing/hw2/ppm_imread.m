function output = ppm_imread(input)
% ppm_imread - Reads ppm image from a file.
% input:filename  

    file = fopen(input); %  open file
    if file == -1 % if file not found
        error('File not found');
    end
    info_str = fgetl(file); % read first line to get image type, P3 is ascii ppm, p6 is binary ppm
    info_str = info_str(2:end); % remove first character 'P' to make string only contain number and space
    info = str2num(info_str); % convert info str to number
    [img_type, width, length, range] = deal(info(1), info(2), info(3), info(4)); % get image type, width, height, range of value
    if info(1) == 3 % if image type is ascii ppm
        for i = 1:length
            for j = 1:width
                for k = 1:3
                    num = 0;
                    ch = fread(file, 1, 'uint8'); % read one byte
                    % read value in ascii
                    while (~feof(file)) && (ch ~= 10) && (ch~=32)
                        num = num * 10 + ch - 48;
                        ch = fread(file, 1, 'uint8');
                    end
                    output(i, j, k) = uint8(num); % convert value to uint8
                end
            end
        end
    elseif info(1) == 6 % if image type is binary ppm
        for i = 1:length
            for j = 1:width
                for k = 1:3
                    ch = fread(file, 1, 'uint8'); % read value
                    output(i, j, k) = uint8(ch); % convert to uint8
                end
            end
        end
    else
        error('Unsupported image type');
    end
end