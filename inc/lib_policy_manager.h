#ifndef _LIB_POLICY_MANAGER_H_
#define _LIB_POLICY_MANAGER_H_

typedef struct _policy_request policy_request;
typedef struct _policy_list policy_list;

/**
 * Create an empty POLICY REQUEST object
 *
 * \return a new POLICY REQUEST object
 */
policy_request *
policy_request_new();

/**
 * Destory POLICY REQUEST object
 *
 * \param a_request POLICY REQUEST object
 */
void
policy_request_destory(policy_request *a_request);

/**
 * Create an empty POLICY LIST object
 *
 * \return a new POLICY LIST object
 */
policy_list *
policy_list_new();

/**
 * Destory POLICY LIST object
 *
 * \param a_list POLICY LIST object
 */
void
policy_list_destory(policy_list *a_list);

/**
 * Parse POLICY LIST content
 *
 * \param a_request POLICY REQUEST object
 * \param a_list POLICY LIST object
 * \return 0 success , -1 fail
 */
int
policy_list_parse(policy_request *a_request, policy_list *a_list);

/**
 * Add a policy
 *
 * \param a_request POLICY REQUEST object
 * \return 0 success , -1 fail
 */
int
policy_add(policy_request *a_request);

/**
 * Delete a policy
 *
 * \param a_request POLICY REQUEST object
 * \return 0 success , -1 fail
 */
int
policy_del(policy_request *a_request);

/**
 * Query policy lists
 *
 * \param a_request POLICY REQUEST object
 * \param a_list POLICY LIST object
 * \return 0 success , -1 fail
 */
int
policy_query(policy_request *a_request, policy_list *a_list);

#endif