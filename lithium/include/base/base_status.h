#ifndef LI_BASE_STATUS_H
#define LI_BASE_STATUS_H

typedef enum {
	LI_STATUS_SUCCESS = 0,
	LI_STATUS_NULL_ARGUMENT,
	LI_STATUS_FAILED_ALLOC,
	LI_STATUS_ARENA_OUT_OF_MEMORY,
	LI_STATUS_FAILED_MEMORY_RELEASE
} LiStatus;

#define liReturnOnFail(status) { if (status != LI_STATUS_SUCCESS) { return status; } }

#endif // LI_BASE_STATUS_H
