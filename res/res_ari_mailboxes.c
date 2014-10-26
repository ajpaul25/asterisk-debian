/*
 * Asterisk -- An open source telephony toolkit.
 *
 * Copyright (C) 2013, Digium, Inc.
 *
 * Jonathan Rose <jrose@digium.com>
 *
 * See http://www.asterisk.org for more information about
 * the Asterisk project. Please do not directly contact
 * any of the maintainers of this project for assistance;
 * the project provides a web site, mailing lists and IRC
 * channels for your use.
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */

/*
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * !!!!!                               DO NOT EDIT                        !!!!!
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * This file is generated by a mustache template. Please see the original
 * template in rest-api-templates/res_ari_resource.c.mustache
 */

/*! \file
 *
 * \brief Mailboxes resources
 *
 * \author Jonathan Rose <jrose@digium.com>
 */

/*** MODULEINFO
	<depend type="module">res_ari</depend>
	<depend type="module">res_stasis</depend>
	<support_level>core</support_level>
 ***/

#include "asterisk.h"

ASTERISK_FILE_VERSION(__FILE__, "$Revision: 419592 $")

#include "asterisk/app.h"
#include "asterisk/module.h"
#include "asterisk/stasis_app.h"
#include "ari/resource_mailboxes.h"
#if defined(AST_DEVMODE)
#include "ari/ari_model_validators.h"
#endif

#define MAX_VALS 128

/*!
 * \brief Parameter parsing callback for /mailboxes.
 * \param get_params GET parameters in the HTTP request.
 * \param path_vars Path variables extracted from the request.
 * \param headers HTTP headers.
 * \param[out] response Response to the HTTP request.
 */
static void ast_ari_mailboxes_list_cb(
	struct ast_tcptls_session_instance *ser,
	struct ast_variable *get_params, struct ast_variable *path_vars,
	struct ast_variable *headers, struct ast_ari_response *response)
{
	struct ast_ari_mailboxes_list_args args = {};
	RAII_VAR(struct ast_json *, body, NULL, ast_json_unref);
#if defined(AST_DEVMODE)
	int is_valid;
	int code;
#endif /* AST_DEVMODE */

	ast_ari_mailboxes_list(headers, &args, response);
#if defined(AST_DEVMODE)
	code = response->response_code;

	switch (code) {
	case 0: /* Implementation is still a stub, or the code wasn't set */
		is_valid = response->message == NULL;
		break;
	case 500: /* Internal Server Error */
	case 501: /* Not Implemented */
		is_valid = 1;
		break;
	default:
		if (200 <= code && code <= 299) {
			is_valid = ast_ari_validate_list(response->message,
				ast_ari_validate_mailbox_fn());
		} else {
			ast_log(LOG_ERROR, "Invalid error response %d for /mailboxes\n", code);
			is_valid = 0;
		}
	}

	if (!is_valid) {
		ast_log(LOG_ERROR, "Response validation failed for /mailboxes\n");
		ast_ari_response_error(response, 500,
			"Internal Server Error", "Response validation failed");
	}
#endif /* AST_DEVMODE */

fin: __attribute__((unused))
	return;
}
/*!
 * \brief Parameter parsing callback for /mailboxes/{mailboxName}.
 * \param get_params GET parameters in the HTTP request.
 * \param path_vars Path variables extracted from the request.
 * \param headers HTTP headers.
 * \param[out] response Response to the HTTP request.
 */
static void ast_ari_mailboxes_get_cb(
	struct ast_tcptls_session_instance *ser,
	struct ast_variable *get_params, struct ast_variable *path_vars,
	struct ast_variable *headers, struct ast_ari_response *response)
{
	struct ast_ari_mailboxes_get_args args = {};
	struct ast_variable *i;
	RAII_VAR(struct ast_json *, body, NULL, ast_json_unref);
#if defined(AST_DEVMODE)
	int is_valid;
	int code;
#endif /* AST_DEVMODE */

	for (i = path_vars; i; i = i->next) {
		if (strcmp(i->name, "mailboxName") == 0) {
			args.mailbox_name = (i->value);
		} else
		{}
	}
	ast_ari_mailboxes_get(headers, &args, response);
#if defined(AST_DEVMODE)
	code = response->response_code;

	switch (code) {
	case 0: /* Implementation is still a stub, or the code wasn't set */
		is_valid = response->message == NULL;
		break;
	case 500: /* Internal Server Error */
	case 501: /* Not Implemented */
	case 404: /* Mailbox not found */
		is_valid = 1;
		break;
	default:
		if (200 <= code && code <= 299) {
			is_valid = ast_ari_validate_mailbox(
				response->message);
		} else {
			ast_log(LOG_ERROR, "Invalid error response %d for /mailboxes/{mailboxName}\n", code);
			is_valid = 0;
		}
	}

	if (!is_valid) {
		ast_log(LOG_ERROR, "Response validation failed for /mailboxes/{mailboxName}\n");
		ast_ari_response_error(response, 500,
			"Internal Server Error", "Response validation failed");
	}
#endif /* AST_DEVMODE */

fin: __attribute__((unused))
	return;
}
int ast_ari_mailboxes_update_parse_body(
	struct ast_json *body,
	struct ast_ari_mailboxes_update_args *args)
{
	struct ast_json *field;
	/* Parse query parameters out of it */
	field = ast_json_object_get(body, "oldMessages");
	if (field) {
		args->old_messages = ast_json_integer_get(field);
	}
	field = ast_json_object_get(body, "newMessages");
	if (field) {
		args->new_messages = ast_json_integer_get(field);
	}
	return 0;
}

/*!
 * \brief Parameter parsing callback for /mailboxes/{mailboxName}.
 * \param get_params GET parameters in the HTTP request.
 * \param path_vars Path variables extracted from the request.
 * \param headers HTTP headers.
 * \param[out] response Response to the HTTP request.
 */
static void ast_ari_mailboxes_update_cb(
	struct ast_tcptls_session_instance *ser,
	struct ast_variable *get_params, struct ast_variable *path_vars,
	struct ast_variable *headers, struct ast_ari_response *response)
{
	struct ast_ari_mailboxes_update_args args = {};
	struct ast_variable *i;
	RAII_VAR(struct ast_json *, body, NULL, ast_json_unref);
#if defined(AST_DEVMODE)
	int is_valid;
	int code;
#endif /* AST_DEVMODE */

	for (i = get_params; i; i = i->next) {
		if (strcmp(i->name, "oldMessages") == 0) {
			args.old_messages = atoi(i->value);
		} else
		if (strcmp(i->name, "newMessages") == 0) {
			args.new_messages = atoi(i->value);
		} else
		{}
	}
	for (i = path_vars; i; i = i->next) {
		if (strcmp(i->name, "mailboxName") == 0) {
			args.mailbox_name = (i->value);
		} else
		{}
	}
	/* Look for a JSON request entity */
	body = ast_http_get_json(ser, headers);
	if (!body) {
		switch (errno) {
		case EFBIG:
			ast_ari_response_error(response, 413, "Request Entity Too Large", "Request body too large");
			goto fin;
		case ENOMEM:
			ast_ari_response_error(response, 500, "Internal Server Error", "Error processing request");
			goto fin;
		case EIO:
			ast_ari_response_error(response, 400, "Bad Request", "Error parsing request body");
			goto fin;
		}
	}
	if (ast_ari_mailboxes_update_parse_body(body, &args)) {
		ast_ari_response_alloc_failed(response);
		goto fin;
	}
	ast_ari_mailboxes_update(headers, &args, response);
#if defined(AST_DEVMODE)
	code = response->response_code;

	switch (code) {
	case 0: /* Implementation is still a stub, or the code wasn't set */
		is_valid = response->message == NULL;
		break;
	case 500: /* Internal Server Error */
	case 501: /* Not Implemented */
	case 404: /* Mailbox not found */
		is_valid = 1;
		break;
	default:
		if (200 <= code && code <= 299) {
			is_valid = ast_ari_validate_void(
				response->message);
		} else {
			ast_log(LOG_ERROR, "Invalid error response %d for /mailboxes/{mailboxName}\n", code);
			is_valid = 0;
		}
	}

	if (!is_valid) {
		ast_log(LOG_ERROR, "Response validation failed for /mailboxes/{mailboxName}\n");
		ast_ari_response_error(response, 500,
			"Internal Server Error", "Response validation failed");
	}
#endif /* AST_DEVMODE */

fin: __attribute__((unused))
	return;
}
/*!
 * \brief Parameter parsing callback for /mailboxes/{mailboxName}.
 * \param get_params GET parameters in the HTTP request.
 * \param path_vars Path variables extracted from the request.
 * \param headers HTTP headers.
 * \param[out] response Response to the HTTP request.
 */
static void ast_ari_mailboxes_delete_cb(
	struct ast_tcptls_session_instance *ser,
	struct ast_variable *get_params, struct ast_variable *path_vars,
	struct ast_variable *headers, struct ast_ari_response *response)
{
	struct ast_ari_mailboxes_delete_args args = {};
	struct ast_variable *i;
	RAII_VAR(struct ast_json *, body, NULL, ast_json_unref);
#if defined(AST_DEVMODE)
	int is_valid;
	int code;
#endif /* AST_DEVMODE */

	for (i = path_vars; i; i = i->next) {
		if (strcmp(i->name, "mailboxName") == 0) {
			args.mailbox_name = (i->value);
		} else
		{}
	}
	ast_ari_mailboxes_delete(headers, &args, response);
#if defined(AST_DEVMODE)
	code = response->response_code;

	switch (code) {
	case 0: /* Implementation is still a stub, or the code wasn't set */
		is_valid = response->message == NULL;
		break;
	case 500: /* Internal Server Error */
	case 501: /* Not Implemented */
	case 404: /* Mailbox not found */
		is_valid = 1;
		break;
	default:
		if (200 <= code && code <= 299) {
			is_valid = ast_ari_validate_void(
				response->message);
		} else {
			ast_log(LOG_ERROR, "Invalid error response %d for /mailboxes/{mailboxName}\n", code);
			is_valid = 0;
		}
	}

	if (!is_valid) {
		ast_log(LOG_ERROR, "Response validation failed for /mailboxes/{mailboxName}\n");
		ast_ari_response_error(response, 500,
			"Internal Server Error", "Response validation failed");
	}
#endif /* AST_DEVMODE */

fin: __attribute__((unused))
	return;
}

/*! \brief REST handler for /api-docs/mailboxes.{format} */
static struct stasis_rest_handlers mailboxes_mailboxName = {
	.path_segment = "mailboxName",
	.is_wildcard = 1,
	.callbacks = {
		[AST_HTTP_GET] = ast_ari_mailboxes_get_cb,
		[AST_HTTP_PUT] = ast_ari_mailboxes_update_cb,
		[AST_HTTP_DELETE] = ast_ari_mailboxes_delete_cb,
	},
	.num_children = 0,
	.children = {  }
};
/*! \brief REST handler for /api-docs/mailboxes.{format} */
static struct stasis_rest_handlers mailboxes = {
	.path_segment = "mailboxes",
	.callbacks = {
		[AST_HTTP_GET] = ast_ari_mailboxes_list_cb,
	},
	.num_children = 1,
	.children = { &mailboxes_mailboxName, }
};

static int load_module(void)
{
	int res = 0;
	stasis_app_ref();
	res |= ast_ari_add_handler(&mailboxes);
	return res;
}

static int unload_module(void)
{
	ast_ari_remove_handler(&mailboxes);
	stasis_app_unref();
	return 0;
}

AST_MODULE_INFO(ASTERISK_GPL_KEY, AST_MODFLAG_DEFAULT, "RESTful API module - Mailboxes resources",
	.support_level = AST_MODULE_SUPPORT_CORE,
	.load = load_module,
	.unload = unload_module,
	.nonoptreq = "res_ari,res_stasis",
	);
