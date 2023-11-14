/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_client_infos.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssefboughanmi <youssefboughanmi@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:31:56 by youssefboug       #+#    #+#             */
/*   Updated: 2023/11/07 15:24:38 by youssefboug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"utils.hpp"
#include"../include/server.hpp"


void Server::get_client_infos(const char *buffer, int fd)
{
    this->client_map[fd].setIdSocket(fd);
    std::string bufferstr(buffer);

    size_t posNick = bufferstr.find("NICK ");
    if (posNick != std::string::npos) {
        size_t posNewline = bufferstr.find('\n', posNick);
        if (posNewline != std::string::npos) {
            std::string nick = bufferstr.substr(posNick + 5, posNewline - (posNick + 6));
            this->client_map[fd].setNick(nick);
        }
    }

    size_t posUser = bufferstr.find("USER ");
    if (posUser != std::string::npos) {
        size_t posNewline = bufferstr.find('\n', posUser);
        if (posNewline != std::string::npos) {
            std::string user = bufferstr.substr(posUser + 5, posNewline - (posUser + 5));
            size_t test = user.find(' ', 0);
            if (test != std::string::npos) {
                std::string user1 = user.substr(0, test);
                this->client_map[fd].setUser(user1);
            }
        }
    }
}