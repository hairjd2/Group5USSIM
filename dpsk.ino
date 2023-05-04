// int index = 0;
// int transmit = 0;
// int DPSK = 1;
// int to = 1;
// int length = 4094;

// while (transmit)
// {
//     if (to)
//     {
//         if (DPSK)
//         {
//             index += length/2;
//             index %= length;
//             dac.setVoltage(dacValue[index], false);
//             index +=1;
//             index %= length;
//         }else{
//             dac.setVoltage(dacValue[index], false);
//             index +=1;
//             index %= length;
//         }
        
//     }else{
//         if (DPSK)
//         {
//             if (index - length/2 < 0){
//                 index = length - (length/2 - index);
//             }else{
//                 index -= length/2;
//             }
//             dac.setVoltage(dacValue[index], false);
//             if (index - 1 < 0){
//                 index = length - 1;
//             }else{
//                 index -= 1;
//             }
//         }else{
//             dac.setVoltage(dacValue[index], false);
//             if (index - 1 < 0){
//                 index = length - 1;
//             }else{
//                 index -= 1;
//             }
//         }
//     }
    
// }
