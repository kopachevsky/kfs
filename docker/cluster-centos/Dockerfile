FROM gluster/gluster-centos

ADD gluster-disc-setup.service /etc/systemd/system/gluster-disc-setup.service
ADD gluster-disc-setup.sh /usr/sbin/gluster-disc-setup.sh

RUN chmod 644 /etc/systemd/system/gluster-disc-setup.service && \
    chmod 755 /usr/sbin/gluster-disc-setup.sh && \
    systemctl enable gluster-disc-setup.service

CMD ["/usr/sbin/init"]