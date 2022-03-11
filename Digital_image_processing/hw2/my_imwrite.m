function [] = my_imwrite(image, filename, encode)
% my_imwrite(): write image to pgm/pbm/ppm file
% image: image matrix
% filename: file name with extension
% encode: ascii or rawbits

    file = fopen(filename, 'wb');
    img_size = size(image);
    if ~contains(extension, '.')
        error('File extension not specified');
    end
    cell_str = strsplit(filename, '.');
    extension = cell_str{2};
    % judge img_type
    if strcmp(extension, 'pbm')
        if strcmp(encode, 'ascii')
            img_type = 'P1';
        elseif strcmp(encode, 'rawbits')
            img_type = 'P4';
        else 
            error('error encode type');
        end
    elseif strcmp(extension, 'pgm')
        if strcmp(encode, 'ascii')
            img_type = 'P2';
        elseif strcmp(encode, 'rawbits')
            img_type = 'P5';
        else 
            error('error encode type');
        end
    elseif strcmp(extension, 'ppm')
        if strcmp(encode, 'ascii')
            img_type = 'P3';
        elseif strcmp(encode, 'rawbits') 
            img_type = 'P6';
        else 
            error('error encode type');
        end
    else 
        error('error extension');
    end
    % write header
    img_head = [img_type, ' ', num2str(img_size(2)), ' ', num2str(img_size(1))];
    if (strcmp(img_type, 'P1')) || (strcmp(img_type, 'P4')) % pbm file only have 3 flags
        img_head = [img_head, char(10)];
    else % pgm/ppm file have 4 flags
        img_head = [img_head, ' ', num2str(255), char(10)];
    end
    fwrite(file, img_head);
    % write data
    % pbm or ppm in ascii
    if (strcmp(img_type, 'P1')) || (strcmp(img_type, 'P2'))  
        if ndims(image) == 3 %if image is rgb, convert to gray
            image = rgb2gray(image);
        end
        for i = 1:img_size(1)
            for j = 1:img_size(2)
                cnt = 1;
                num = uint8(image(i,j));
                % if image is pbm, convert gray value to 0/1
                if strcmp(img_type, 'P1')
                    if num >= 128
                        num = 0;
                    else
                        num = 1;
                    end
                end
                fwrite(file, num2str(num)); % write ascii num to file
                fwrite(file, ' ');
            end 
        end
    % ppm in ascii
    elseif strcmp(img_type, 'P3')
        for i = 1:img_size(1)
            for j = 1:img_size(2)
                for k = 1:3
                    cnt = 1;
                    num = uint8(image(i,j,k));
                    fwrite(file, num2str(num)); % write ascii num to file
                    fwrite(file, ' ');
                end 
            end
        end
    % pbm in binary
    elseif strcmp(img_type, 'P4')
        if ndims(image) == 3 %if image is rgb
            image = rgb2gray(image);
        end
        cnt = 0;
        num = 0;
        for i = 1:img_size(1)
            for j = 1:img_size(2)
                num1 = uint8(image(i,j));
                % if image is pbm, convert gray value to 0/1
                if num1 >= 128
                    num1 = 1;
                else
                    num1 = 0;
                end
                num = num * 2  + 1 - num1;
                cnt = cnt + 1;
                % if cnt is 8, write num to file
                if cnt == 8
                    cnt = 0;
                    fwrite(file, num); % write binary num to file
                    num = 0;
                end
            end
            if cnt ~= 0
                while cnt < 8
                    num = num * 2 + 1;
                    cnt = cnt + 1;
                end
                fwrite(file, num); % write binary num to file
                cnt = 0;
                num = 0;
            end
        end
    % pgm in binary
    elseif strcmp(img_type, 'P5')
        if ndims(image) == 3 %if image is rgb
            image = rgb2gray(image);
        end
        for i = 1:img_size(1)
            for j = 1:img_size(2)
                fwrite(file, uint8(image(i,j)));
            end
        end
    % ppm in binary
    else
        for i = 1:img_size(1)
            for j = 1:img_size(2)
                for k = 1:3
                    fwrite(file, uint8(image(i,j,k)));
                end
            end
        end
    end
    fclose(file);
end