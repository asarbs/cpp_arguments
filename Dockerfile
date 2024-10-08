FROM debian


USER root

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

COPY .devcontainer/library-scripts/*.sh /tmp/library-scripts/
RUN apt-get update
RUN apt-get upgrade -y \
    && bash /tmp/library-scripts/common-debian.sh
RUN apt-get install -y bash bash-completion python3 python3-django python3-pip git python3-bs4 sqlite3 wget lsb-release software-properties-common gnupg clang-format gdb

SHELL ["/bin/bash", "-c"]

EXPOSE 3000

USER ${USERNAME}

ENTRYPOINT [ "/usr/local/share/docker-init.sh" ]
CMD [ "sleep", "infinity" ]
