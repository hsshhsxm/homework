function output = my_imread(input)
% my_imread(): Reads pbm/pgm/ppm image from a file.
% input:filename  

    file = fopen(input); %  open file
    if file == -1 % if file not found
        error('File not found');
    end
    info_str = fgetl(file); % read first line to get image type, P1~P6
    info_str = info_str(2:end); % remove first character 'P' to make string only contain number and space
    info = str2num(info_str); % convert info str to number
    [img_type, width, length] = deal(info(1), info(2), info(3)); % get image type, width, height, range of value
    if info(1) <= 3 % if image type is ascii
        if info(1) == 3 % ppm
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
        else % pbm or pgm
            for i = 1:length
                for j = 1:width
                    num = 0;
                    ch = fread(file, 1, 'uint8'); % read one byte
                    % read value in ascii
                    while (~feof(file)) && (ch ~= 10) && (ch~=32)
                        num = num * 10 + ch - 48;
                        ch = fread(file, 1, 'uint8');
                    end
                    if info(1) == 1 % pbm
                        output(i, j) = 1 - num;
                    else % pgm
                        output(i, j) = uint8(num);
                    end
                end
            end
        end
    else % if image type is binary
        if info(1) == 6 % ppm
            for i = 1:length
                for j = 1:width
                    for k = 1:3
                        ch = fread(file, 1, 'uint8'); % read value
                        output(i, j, k) = uint8(ch); % convert to uint8
                    end
                end
            end
        elseif info(1) == 5 % pgm
            for i = 1:length
                for j = 1:width
                    ch = fread(file, 1, 'uint8'); % read value
                    output(i, j) = uint8(ch); % convert to uint8
                end
            end
        elseif info(1) == 4 % pbm
            ch = fread(file, 1, 'uint8'); 
            for k = 1:8 % convert number to binary and store in bits
                bits(k) = mod(ch, 2);
                ch = fix(ch / 2);
            end
            cnt = 8;
            for i = 1:length
                for j = 1:width
                    output(i, j) = 1 - bits(cnt); % set value
                    cnt = cnt - 1;
                    if cnt == 0
                        ch = fread(file, 1, 'uint8');
                        cnt = 8;
                        for k = 1:8 % convert number to binary and store in bits
                            bits(k) = mod(ch, 2);
                            ch = fix(ch / 2);
                        end
                    end
                end
                if i ~= length
                    ch = fread(file, 1, 'uint8');
                    cnt = 8;
                    for k = 1:8 % convert number to binary and store in bits
                        bits(k) = mod(ch, 2);
                        ch = fix(ch / 2);
                    end
                end
            end
        else 
            error('Unknown image type');
        end
    end
end