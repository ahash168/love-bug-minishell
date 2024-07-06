/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:27:05 by ahashem           #+#    #+#             */
/*   Updated: 2024/06/26 16:19:31 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

pipeline>          ::=     <simple_command>    '|' <pipeline>
                      |     <simple_command>    'ε'

<simple_command>    ::=     <io_list>           <word><cmd_suffix>
                      |     <io_list>           <word>
                      |     <io_list>
                      |     <word>              <cmd_suffix>
                      |     <word>

<io_list>           ::=     <io_redirect>       <io_list>
                      |     <io_redirect>

<cmd_suffix>        ::=     <io_list>           <cmd_suffix>
                      |     <io_list>
                      |     <word>              <cmd_suffix>
                      |     <word>

<io_redirect>       ::=     '<'             <word>
                      |     '>'             <word>
                      |     '>>'            <word>
                      |     '<<'            <word>




so basically for the recursion method it uses this method, its a little too complicated to
debug but we  will use this to have a sense of the "grammar" or syntax of the actuall shell,
just to have a sense of what to actually work on and how the parsing should go. so we should
start by building smth that will split and say thats a word or an operator, then another function
that goes over that and identifies the "type"/give it meaning as in command or file etc.
and thennn only can we check the grammar being correct or not

now in general this is a process that has to repeat itself over and over again as the user
is allowed to input commands several times, so we can allocate get the data deal with it execute
then free to allow the user to input again

