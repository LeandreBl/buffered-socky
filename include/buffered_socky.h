#ifndef BUFFERED_SOCKY_H
#define BUFFERED_SOCKY_H

#include <buffy.h>
#include <socky.h>

/**
 * \struct buffered_socky
 * \brief The buffered_socky structure.
 * 
 * This structure is used to represent a buffered socket.
 * It is a wrapper around a socky structure.
 * It is used to buffer data sent and received from a socket.
 * 
 * \var socky: The socky socket wrapper structure.
 * \var buffy_reader: The buffy structure used to buffer data received from the socket.
 * \var buffy_writer: The buffy structure used to buffer data sent to the socket.
 */
struct buffered_socky {
    struct socky socky;
    struct buffy buffy_reader;
    struct buffy buffy_writer;
};

/**
 * \struct
 * 
 * \brief The buffered_socky_create params.
 * 
 * \note This structure is used to pass parameters to the buffered_socky_create function.
 * 
 * \var socky_protocol: The protocol of the socket.
 * \var read_buffy_allocation_strategy: The allocation strategy of the read buffy.
 * \var read_buffy_capacity: The capacity of the read buffy.
 * \var write_buffy_allocation_strategy: The allocation strategy of the write buffy.
 * \var write_buffy_capacity: The capacity of the write buffy.
 */
struct buffered_socky_params {
    enum socky_protocol protocol;
    enum buffy_allocation_strategy buffy_reader_allocation_strategy;
    size_t buffy_reader_capacity;
    enum buffy_allocation_strategy buffy_writer_allocation_strategy;
    size_t buffy_writer_capacity;
};

/**
 * \fn int socky_create(struct buffered_socky *bsocky, enum socky_protocol protocol)
 * 
 * \brief Open a socket and set it's protocol for later use.
 * 
 * \param bsocky The socket to create.
 * \param proto The protocol of the socket.
 * 
 * \return 0 on success, -1 on error, errno is set accordingly.
 */
int buffered_socky_create(struct buffered_socky *bsocky, const struct buffered_socky_params *params) __nonnull((1, 2));

/**
 * \fn int buffered_socky_create_from_socky(struct buffered_socky *bsocky, const struct socky *socky, enum socky_protocol protocol)
 * 
 * \brief Create a buffered socky from a socky
 * 
 * \param bsocky The buffered socket to create.
 * \param socky The socket to use in this buffered socket
 * \param proto The protocol of the socket.
 * 
 * \return 0 on success, -1 on error, errno is set accordingly.
 */
int buffered_socky_create_from_socky(struct buffered_socky *bsocky, const struct socky *socky, const struct buffered_socky_params *params) __nonnull((1, 2, 3));


/**
 * \fn int buffered_socky_destroy(struct buffered_socky *bsocky)
 * 
 * \brief Destroy a buffered socket.
 * 
 * \param bsocky The socket to destroy.
 */
void buffered_socky_destroy(struct buffered_socky *bsocky) __nonnull((1));

/**
 * \fn int buffered_socky_write(struct buffered_socky *bsocky, const void *data, size_t size)
 * 
 * \brief Write data to a buffered socket and store it into the buffy write buffer.
 * 
 * \note This function does not directly write onto the socket, it fills a buffer with the data, a following call to buffered_socky_flush will write the data to the socket.
 * 
 * \param bsocky The socket to write to.
 * \param data The data to write.
 * \param size The size of the data to write.
 * 
 * \return The number of bytes written on success, -1 on error, errno is set accordingly.
 */
ssize_t buffered_socky_write(struct buffered_socky *bsocky, const void *data, size_t size) __nonnull((1, 2));

/**
 * \fn int buffered_socky_flush(struct buffered_socky *bsocky)
 * 
 * \brief Flush the buffer to write of a buffered socket.
 * 
 * \note This function is the equivalent of calling buffered_socky_flushf with flags set to 0.
 * 
 * \param bsocky The socket to flush.
 * 
 * \return The number of bytes flushed on success, -1 on error, errno is set accordingly.
 */
ssize_t buffered_socky_flush(struct buffered_socky *bsocky) __nonnull((1));

/**
 * \fn int buffered_socky_flushf(struct buffered_socky *bsocky, int flags)
 * 
 * \brief Flush the buffer to write of a buffered socket with given flags, this function uses send with the given flags.
 * 
 * \param bsocky The socket to flush.
 * \param flags The flags to use for the send (see man 2 send)
 * 
 * \return The number of bytes flushed on success, -1 on error, errno is set accordingly.
 */
ssize_t buffered_socky_flushf(struct buffered_socky *bsocky, int flags) __nonnull((1));

/**
 * \fn int buffered_socky_read(struct buffered_socky *bsocky, void *data, size_t size)
 * 
 * \brief Read data from a buffered socket and store it into the buffy_reader buffer.
 * 
 * \note This function is the equivalent of calling buffered_socky_recv with flags set to 0.
 * 
 * \param bsocky The socket to read from.
 * \param size The size of the data to read.
 * 
 * \return The number of bytes read on success, -1 on error, errno is set accordingly.
 */
ssize_t buffered_socky_read(struct buffered_socky *bsocky, size_t size) __nonnull((1));

/**
 * \fn int buffered_socky_read(struct buffered_socky *bsocky, void *data, size_t size)
 * 
 * \brief Read data from a buffered socket and store it into the buffy_reader buffer, this function uses recv with the given flags.
 * 
 * \param bsocky The socket to read from.
 * \param data The data to read.
 * \param size The size of the data to read.
 * \param flags The flags to use when reading (see man 2 recv)
 * 
 * \return The number of bytes read on success, -1 on error, errno is set accordingly.
 */
ssize_t buffered_socky_recv(struct buffered_socky *bsocky, size_t size, int flags) __nonnull((1));

#endif /* !BUFFERED_SOCKY_H */