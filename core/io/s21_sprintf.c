#include "s21_sprintf.h"

#include "digits.h"

int s21_sprintf(char *str, const char *format, ...) {
  // if (!str || !format) return -1;
  va_list args;
  va_start(args, format);
  char *cursor = str;
  while (*cursor) cursor++;
  const char *format_cur = format;
  int cnt = 0;
  while (*format_cur && cnt >= 0) {
    int is_checked = 0;
    if (*format_cur == '%' && !is_checked) {
      const char *temp_format_cur = format_cur;
      specs *options = parse_format(&format_cur, &args);
      if (!options->spec) format_cur = temp_format_cur + 1;
      int len = process_specs(&args, &cursor, options);
      cnt = -1 * (len < 0) + (cnt + len) * (len >= 0);
      free(options);
      is_checked = 1;
    } else {
      *cursor++ = *format_cur;
      cnt++;
      format_cur++;
      *cursor = '\0';
    }
  }

  va_end(args);
  return cnt;
}
/*
  Принцип работы функции process_specs:
    Функция получает на вход список всех оставшихся переменных,
    проверяет содержится ли после процента какой-либо спецификатор
    и запускает для каждого спецификатора свою функцию.

    В процессе работы эта функция меняет все входящие переменные:
    cursor - чтобы нам не приходилось каждый раз бежать до конца строки, когда
    мы хотим что-то в нее добавить, format - сдвигается до конца текущего
    спецификатора,

    Возвращает эта функция длину добавленного блока,
    в случае любой ошибки возращает -1
*/

/*
  Принцип работы функций для всех спецификаторов:
  Берет значение переменной из списка переменных args,
  применяет все необходимые флаги, которые находятся в строке format_cur до
  указателя format_end, Считает длину добавляемого блока, в случае ошибке длина
  блока = -1; конкатинирует полученный блок с cursor, Смещает cursor на длину
  блока.
*/

int process_specs(va_list *args, char **cursor, const specs *options) {
  int len = 0;
  switch (options->spec) {
    case 'c':
      len += spec_c((char)va_arg(*args, int), options, cursor);
      break;
    case 'd':
      len += spec_ints(va_arg(*args, long long int), 10, options, cursor);
      break;
    case 'i':
      len += spec_ints(va_arg(*args, long long int), 10, options, cursor);
      break;
    case 'e':
    case 'E':
      if (options->length[2])
        len += SPEC_E(va_arg(*args, long double), options, cursor);
      else
        len += SPEC_E((double)va_arg(*args, double), options, cursor);
      break;
    case 'f':
      if (options->length[2])
        len += spec_f(va_arg(*args, long double), (specs *)options, cursor);
      else
        len += spec_f((double)va_arg(*args, double), (specs *)options, cursor);
      break;
    case 'g':
    case 'G':
      if (options->length[2])
        len += spec_g(va_arg(*args, long double), (specs *)options, cursor);
      else
        len += spec_g((double)va_arg(*args, double), (specs *)options, cursor);
      break;
    case 'o':
      len += spec_ints(va_arg(*args, long long int), 8, options, cursor);
      break;
    case 's':
      len += spec_s(va_arg(*args, char *), options, cursor);
      break;
    case 'u':
      len += spec_ints(va_arg(*args, long long int), 10, options, cursor);
      break;
    case 'x':
      len += spec_ints(va_arg(*args, long long int), 16, options, cursor);
      break;
    case 'X':
      len += spec_ints(va_arg(*args, long long int), 16, options, cursor);
      break;
    case 'p':
      len += spec_p(va_arg(*args, void *), (specs *)options, cursor);
      break;
    case '%':
      len += spec_percent(cursor);
      break;
  }
  return len;
}

specs *parse_format(const char **format, va_list *args) {
  specs *res = s21_calloc(sizeof(specs));
  const char *specs = "cdieEfgGosuxXpn%";
  const char *flags = "-+ #0";
  const char *length = "hlL";

  (*format)++;
  char *cur_flag = S21_NULL;
  char *result = S21_NULL;
  do {
    while ((cur_flag = s21_strchr(flags, **format)) != S21_NULL) {
      res->flag[cur_flag - flags] = **format;
      (*format)++;
    }
    if (**format == '*') {
      res->width = va_arg(*args, int);
      (*format)++;
    } else {
      res->width = s21_atoi(*format);
      while (**format >= '0' && **format <= '9') (*format)++;
    }
    res->precision = -2;
    if (**format == '.') {
      res->precision = -1;
      (*format)++;
      if (**format == '*') {
        res->precision = va_arg(*args, int);
        (*format)++;
      } else {
        res->precision = s21_atoi(*format);
        while (**format >= '0' && **format <= '9') (*format)++;
      }
    }
    while ((cur_flag = s21_strchr(length, **format)) != S21_NULL) {
      res->length[cur_flag - length]++;
      (*format)++;
    }
    if (**format) result = s21_strchr(specs, **format);
    if (!result) (*format)++;
  } while (!result && **format);

  res->spec = **format;
  res->precision = set_default_precision(res->precision, res->spec);
  if (**format) (*format)++;
  return res;
}

int set_default_precision(int precision, char spec) {
  char *floats = "efgEFG";
  int res = precision;
  if (s21_strchr(floats, spec) && precision < 0) res = 6;
  if (res == -1) res = 1;
  if (precision == 0 && (spec == 'd' || spec == 'i' || spec == 'u' ||
                         spec == 'o' || spec == 'x' || spec == 'X'))
    res = -1;
  return res;
}

int spec_c(char value, const specs *options, char **cursor) {
  int width = options->width > 0 ? options->width : 0;
  int len = width > 1 ? width : 1;

  char *buffer = (char *)s21_calloc(len + 1);
  if (!buffer) return -1;

  if (options->flag[0] == '-') {
    buffer[0] = value;
    s21_memset(buffer + 1, ' ', len - 1);
  } else {
    s21_memset(buffer, ' ', len - 1);
    buffer[len - 1] = value;
  }

  s21_strncat(*cursor, buffer, len);
  *cursor += len;

  free(buffer);
  return len;
}

int spec_s(const char *value, const specs *options, char **cursor) {
  const char *str = (value == S21_NULL) ? "(nil)" : value;
  int str_len = s21_strlen(str);

  int total_len = (options->width > str_len) ? options->width : str_len;

  if (options->flag[0] == '-') {
    s21_strncat(*cursor, str, str_len);

    s21_memset(*cursor + str_len, ' ', total_len - str_len);
  } else {
    s21_memset(*cursor, ' ', total_len - str_len);

    s21_strncat(*cursor + (total_len - str_len), str, str_len);
  }

  if (options->precision < str_len && options->precision >= 0) {
    *cursor += options->precision;
    **cursor = '\0';
    total_len = options->precision;
  } else
    *cursor += total_len;

  return total_len;
}

int spec_percent(char **cursor) {
  s21_strncat(*cursor, "%", 1);
  (*cursor)++;
  return 1;
}

int spec_ints(long long int value, int base, const specs *options,
              char **cursor) {
  char buffer[BUF_SIZE] = {0};
  char *ptr = buffer;

  int unsigned_value = options->spec == 'u' || options->spec == 'x' ||
                       options->spec == 'X' || options->spec == 'o';

  if (unsigned_value) {
    if (options->length[0])
      S21_ITOA((unsigned short int)value, ptr, base);
    else if (options->length[1] == 1)
      S21_ITOA((unsigned long int)value, ptr, base);
    else if (options->length[1] == 2)
      S21_ITOA((unsigned long long)value, ptr, base);
    else
      S21_ITOA((unsigned int)value, ptr, base);
  } else {
    if (options->length[0])
      S21_ITOA((short int)value, ptr, base);
    else if (options->length[1] == 1)
      S21_ITOA((long int)value, ptr, base);
    else if (options->length[1] == 2)
      S21_ITOA((long long int)value, ptr, base);
    else
      S21_ITOA((int)value, ptr, base);
  }

  if (options->spec == 'X') {
    ptr = s21_to_upper(ptr);
    *buffer = 0;
    s21_strncat(buffer, ptr, s21_strlen(ptr));
    free(ptr);
    ptr = buffer;
  }

  ptr = process_flags(ptr, options);

  int len = s21_strlen(ptr);
  s21_strncat(*cursor, ptr, len);
  *cursor += len;
  return len;
}

int spec_p(void *value, specs *options, char **cursor) {
  int len = 0;
  if (!value) {
    len = s21_sprintf(*cursor, "(nil)");
    *cursor += len;
  } else {
    options->flag[3] = 1;
    options->spec = 'x';
    options->length[1] = 1;
    len = spec_ints((s21_size_t)value, 16, options, cursor);
  }
  return len;
}

int spec_f(long double value, specs *options, char **cursor) {
  char buffer[BUF_SIZE] = {0};
  char *ptr = buffer;
  if (options->length[2])
    ptr = S21_FTOA(ptr, value, options->precision);
  else
    ptr = S21_FTOA(ptr, (double)value, options->precision);
  if (options->spec == 'E') {
    ptr = s21_to_upper(ptr);
    *buffer = 0;
    s21_strncat(buffer, ptr, s21_strlen(ptr));
    free(ptr);
    ptr = buffer;
  }
  options->spec = 'f';
  ptr = process_flags(ptr, options);

  int len = s21_strlen(ptr);
  s21_strncat(*cursor, ptr, len);
  *cursor += len;
  return len;
}

#define SPEC_E_COMMON(type)                                            \
  int spec_e_##type(type value, const specs *options, char **cursor) { \
    char buffer[BUF_SIZE] = {0};                                       \
    char *ptr = buffer;                                                \
    if (options->length[2])                                            \
      ptr = S21_EXPTOA(ptr, value, options->precision);                \
    else                                                               \
      ptr = S21_EXPTOA(ptr, value, options->precision);                \
    ptr = process_flags(ptr, options);                                 \
    if (options->spec == 'E') ptr = s21_to_upper(ptr);                 \
                                                                       \
    int len = s21_strlen(ptr);                                         \
    s21_strncat(*cursor, ptr, len);                                    \
    *cursor += len;                                                    \
    if (options->spec == 'E') free(ptr);                               \
    return len;                                                        \
  }

SPEC_E_COMMON(long_double)
SPEC_E_COMMON(double)

int spec_g(long double value, specs *options, char **cursor) {
  int len = 0;
  options->spec = options->spec == 'G' ? 'E' : options->spec;
  options->precision = spec_g_precision(value, options->precision, options);
  if (options->precision < 0) {
    options->precision = -(options->precision + 1);
    len = spec_f(value, options, cursor);
  } else {
    len = SPEC_E(value, options, cursor);
  }
  return len;
}

int spec_g_cnt_digits(long double value) {
  int cnt = 0;
  if (!value)
    cnt = 1;
  else {
    long double abs = FABS(value);
    while (abs - 1.0L < FLT_EPSILON) {
      abs *= 10.0L;
    }
    while (abs - 1.0L > FLT_EPSILON) {
      abs -= FLOOR(abs);
      abs *= 10.0L;
      cnt++;
    }
  }
  return cnt;
}

int spec_g_precision(long double value, int precision, const specs *options) {
  /*
    (precision + 1) < 0 -> %f
    precision >= 0       -> %e
  */
  int new_precision = precision;
  int exp = (int)FLOOR(LOG10(FABS(value)));
  long double num = FABS(FLOOR(value / POW(10.0, exp)));
  if (FABS(10.0 - num) < FLT_EPSILON) {
    exp++;
  }
  int digits_cnt = spec_g_cnt_digits(value);

  if (exp >= 6 || exp < -4) {
    if (digits_cnt < precision && !options->flag[3])
      new_precision = digits_cnt - 1;
    else if (precision != 0)
      new_precision--;
  } else {
    if (!options->flag[3]) new_precision -= exp;
    if (new_precision > digits_cnt && !options->flag[3])
      new_precision = digits_cnt;
    new_precision *= -1;
    new_precision--;
  }

  if (!value) new_precision = -1;
  return new_precision;
}

char determine_sign_char(char *number, const specs *options) {
  char sign_char = '\0';

  if (number[0] == '-') {
    sign_char = '-';
  } else if (options->flag[1] == '+' &&
             (options->spec == 'd' || options->spec == 'i' ||
              options->spec == 'f' || options->spec == 'e' ||
              options->spec == 'E' || options->spec == 'g' ||
              options->spec == 'G')) {
    sign_char = '+';
  } else if (options->flag[2] == ' ' &&
             (options->spec == 'd' || options->spec == 'i' ||
              options->spec == 'f' || options->spec == 'e' ||
              options->spec == 'E' || options->spec == 'g' ||
              options->spec == 'G')) {
    sign_char = ' ';
  }

  return sign_char;
}

int calculate_precision_padding(int len, const specs *options, char *number) {
  int precision_padding = 0;

  if (options->precision > len && !(number[0] == 'i' || number[0] == 'n' ||
                                    number[0] == 'I' || number[0] == 'N')) {
    precision_padding = options->precision - len;
  }

  return precision_padding;
}

int calculate_width_padding(int total_len, const specs *options) {
  int width_padding = 0;

  if (options->width > total_len) {
    width_padding = options->width - total_len;
  }

  return width_padding;
}

void handle_flag_minus(char **temp_ptr, const char *number, int len,
                       int precision_padding, int width_padding,
                       char sign_char) {
  if (sign_char) *(*temp_ptr)++ = sign_char;

  while (precision_padding-- > 0) {
    *(*temp_ptr)++ = '0';
  }

  s21_strncpy(*temp_ptr, number, len);
  *temp_ptr += len;

  while (width_padding-- > 0) {
    *(*temp_ptr)++ = ' ';
  }
}

void handle_flag_zero(char **ptr, const char *number, int len,
                      int width_padding, char sign_char) {
  if (sign_char) *(*ptr)++ = sign_char;

  while (width_padding-- > 0) {
    *(*ptr)++ = '0';
  }

  s21_strncpy(*ptr, number, len);
  *ptr += len;
}

void handle_default(char **temp_ptr, const char *number, int len,
                    int precision_padding, int width_padding, char sign_char) {
  while (width_padding-- > 0) {
    *(*temp_ptr)++ = ' ';
  }

  if (sign_char) *(*temp_ptr)++ = sign_char;

  while (precision_padding-- > 0) {
    *(*temp_ptr)++ = '0';
  }

  s21_strncpy(*temp_ptr, number, len);
  *temp_ptr += len;
}

void add_prefix_for_flag_hash(char **number, const specs *options,
                              int precision_padding) {
  char *temp_ptr = S21_NULL;
  if (options->spec == 'o' && precision_padding <= 0) {
    temp_ptr = s21_insert(*number, "0", 0);
  } else if (options->spec == 'x' || options->spec == 'X') {
    temp_ptr = s21_insert(*number, options->spec == 'X' ? "0X" : "0x", 0);
  } else {
    temp_ptr = s21_insert(*number, "", 0);
  }
  **number = 0;
  int len = s21_strlen(temp_ptr);
  *number = s21_strncpy(*number, temp_ptr, len);
  *(*number + len) = '\0';
  free(temp_ptr);
}

void add_dot_for_flag_hash(char **number, const specs *options) {
  char *point = S21_NULL;
  if ((options->spec == 'f' || options->spec == 'g' || options->spec == 'G' ||
       options->spec == 'e' || options->spec == 'E') &&
      !(point = s21_strrchr(*number, '.'))) {
    char *exp = s21_strpbrk(*number, "eE");
    char *temp_ptr = S21_NULL;
    if (exp)
      temp_ptr = s21_insert(*number, ".", exp - *number);
    else
      temp_ptr = s21_insert(*number, ".", s21_strlen(*number));
    **number = 0;
    int len = s21_strlen(temp_ptr);
    *number = s21_strncpy(*number, temp_ptr, len);
    *(*number + len) = '\0';
    free(temp_ptr);
  }
}

void handle_flag_hash(char **number, const specs *options, int *len,
                      int precision_padding) {
  if (options->flag[3] &&
      !(s21_strncmp(*number, "0", s21_strlen(*number)) == 0) &&
      (options->spec == 'o' || options->spec == 'x' || options->spec == 'X')) {
    add_prefix_for_flag_hash(number, options, precision_padding);
    *len = s21_strlen(*number);
  }

  if (options->flag[3]) {
    add_dot_for_flag_hash(number, options);
    *len = s21_strlen(*number);
  }
}

void move_prefix_to_start(char *str) {
  char *pos = s21_strpbrk(str, "xX");

  if (pos != S21_NULL && pos != str + 1) {
    char temp = *pos;

    for (char *ptr = pos; ptr > str; ptr--) {
      *(ptr) = *(ptr - 1);
    }

    str[1] = temp;
  }
}

char *process_flags(char *number, const specs *options) {
  char *ptr = number;

  if (s21_strncmp(number, "0", 1) == 0 && (options->precision == -1)) {
    int width = options->width;
    while (width-- > 0) *ptr++ = ' ';
    *ptr = '\0';
    return number;
  }

  int len = s21_strlen(number);
  char sign_char = determine_sign_char(number, options);
  if (sign_char == '-') {
    number++;
    len--;
  }

  int precision_padding = calculate_precision_padding(len, options, number);
  handle_flag_hash(&number, options, &len, precision_padding);

  int total_len = len + precision_padding + (sign_char ? 1 : 0);
  int width_padding = calculate_width_padding(total_len, options);

  char temp_buffer[BUF_SIZE] = {0};
  char *temp_ptr = temp_buffer;

  if (options->flag[0] == '-') {
    handle_flag_minus(&temp_ptr, number, len, precision_padding, width_padding,
                      sign_char);
  } else if (options->flag[4] == '0' &&
             !(number[0] == 'i' || number[0] == 'n' || number[0] == 'I' ||
               number[0] == 'N')) {
    handle_flag_zero(&temp_ptr, number, len, width_padding, sign_char);
  } else {
    handle_default(&temp_ptr, number, len, precision_padding, width_padding,
                   sign_char);
  }

  *temp_ptr = '\0';

  s21_strncpy(number, temp_buffer, s21_strlen(temp_buffer) + 1);
  if (options->flag[4] || precision_padding) move_prefix_to_start(number);

  return number;
}
