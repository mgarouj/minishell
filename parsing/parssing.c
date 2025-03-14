

#include "../minishell.h"




// int find_quote(char *line)
// {
//     int i;

//     i = 0;
//     while(line[i])
//     {
//         if(line[i] == '"')
//             return(++i);
//         i++;
//     }
//     return(0);
// }

// int find_next_quote(char *line)
// {
//     int next;

//     next = find_quote(line);
//     if(next)
//     {
//         return(next);
//     }
//     else
//         return(0);

// }

// int parssing(char *line)
// {
//     int i;
//     int next;

//     i = 0;
//     next = find_quote(line);
//     if(next)
//     {
//         if(find_next_quote(line + next))
//         {
            
//         }
//     }


// }


int find_quote(char *line)
{
    int i;

    i = 0;
    while(line[i])
    {
        if(line[i] == '"')
            return(1);
        i++;
    }
    return(0);
}

int parssing(char *line)
{
    int i;

    i = 0;
    while(line[i])
    {
        if(line[i] == '"')
        {
            i++;
            if(find_quote(line + i))
                i++;
            else
                return(0);
        }
        i++;
    }
    return(1);
}