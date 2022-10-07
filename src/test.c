#include <check.h>

#include "Back.h"

t_universe a;
t_universe *data = &a;
char str[200] = "../obj/pyramide.obj";

START_TEST(parser_test) {
  int ret = 0;
  ret = loading(data, str);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(data->sum_facets, 5);
  ck_assert_int_eq(data->sum_vertexes, 5);
  s21_remove_matrix(&data->matrix_3d);
  for (int i = 0; i < data->sum_facets + 1; i++) {
    free(data->polygons[i].name_vertexes);
  }
  free(data->polygons);
}
END_TEST

START_TEST(test_rotation_about_x) {
  loading(data, str);
  double x = 180;
  matrix_t result = rotating(data, x, 0, 0);

  matrix_t expected_matrix = {0};
  s21_create_matrix(6, 3, &expected_matrix);

  double exp_matrix_0[6][3] = {{0.000000, 0.000000, 0.000000},
                               {1.000000, -0.10134628, -0.69980635},
                               {-1.000000, -0.10134628, -0.69980635},
                               {-1.000000, 0.69980635, -0.10134628},
                               {1.000000, 0.69980635, -0.10134628},
                               {0.000000, -0.29923003, 0.40057631}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expected_matrix.matrix[i][j] = exp_matrix_0[i][j];
    }
  }

  int ret = s21_eq_matrix(&expected_matrix, &result);
  ck_assert_int_eq(1, ret);

  s21_remove_matrix(&expected_matrix);
  s21_remove_matrix(&data->matrix_3d);
  for (int i = 0; i < data->sum_facets + 1; i++) {
    free(data->polygons[i].name_vertexes);
  }
  free(data->polygons);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_rotation_about_y) {
  loading(data, str);
  double y = 90;
  matrix_t result = rotating(data, 0, y, 0);

  matrix_t expected_matrix = {0};
  s21_create_matrix(6, 3, &expected_matrix);

  double exp_matrix_0[6][3] = {
      {0.000000, 0.000000, 0.000000},       {-0.8950719, -0.500000, 0.6699599},
      {0.0010753, -0.500000, -1.1180335},   {0.8950719, -0.500000, -0.6699599},
      {-0.001075335, -0.500000, 1.1180335}, {0.000000, 0.500000, 0.000000}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expected_matrix.matrix[i][j] = exp_matrix_0[i][j];
    }
  }

  int ret = s21_eq_matrix(&expected_matrix, &result);
  ck_assert_int_eq(1, ret);

  s21_remove_matrix(&expected_matrix);
  s21_remove_matrix(&data->matrix_3d);
  for (int i = 0; i < data->sum_facets + 1; i++) {
    free(data->polygons[i].name_vertexes);
  }
  free(data->polygons);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_rotation_about_z) {
  loading(data, str);
  double z = -90;
  matrix_t result = rotating(data, 0, 0, z);

  matrix_t expected_matrix = {0};
  s21_create_matrix(6, 3, &expected_matrix);

  double exp_matrix_0[6][3] = {
      {0.000000, 0.000000, 0.000000},      {-0.0010753, 1.1180335, 0.5000000},
      {0.8950719, -0.6699599, 0.5000000},  {0.8950719, -0.6699599, -0.5000000},
      {-0.0010753, 1.1180335, -0.5000000}, {-0.4469983, -0.2240368, 0.0000000}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expected_matrix.matrix[i][j] = exp_matrix_0[i][j];
    }
  }

  int ret = s21_eq_matrix(&expected_matrix, &result);
  ck_assert_int_eq(1, ret);

  s21_remove_matrix(&expected_matrix);
  s21_remove_matrix(&data->matrix_3d);
  for (int i = 0; i < data->sum_facets + 1; i++) {
    free(data->polygons[i].name_vertexes);
  }
  free(data->polygons);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_scale) {
  loading(data, str);
  matrix_t result = scaling(data, 2, 2, 2);

  matrix_t expected_matrix = {0};
  s21_create_matrix(6, 3, &expected_matrix);

  double exp_matrix_0[6][3] = {
      {0.0000000, 0.0000000, 0.0000000},   {2.0000000, -1.0000000, 1.0000000},
      {-2.0000000, -1.0000000, 1.0000000}, {-2.0000000, -1.0000000, -1.0000000},
      {2.0000000, -1.0000000, -1.0000000}, {0.0000000, 1.0000000, 0.0000000}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expected_matrix.matrix[i][j] = exp_matrix_0[i][j];
    }
  }

  int ret = s21_eq_matrix(&expected_matrix, &result);
  ck_assert_int_eq(1, ret);

  s21_remove_matrix(&expected_matrix);
  s21_remove_matrix(&data->matrix_3d);
  for (int i = 0; i < data->sum_facets + 1; i++) {
    free(data->polygons[i].name_vertexes);
  }
  free(data->polygons);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_move) {
  loading(data, str);
  matrix_t result = moving(data, 2, 3, 4);

  matrix_t expected_matrix = {0};
  s21_create_matrix(6, 3, &expected_matrix);

  double exp_matrix_0[6][3] = {
      {0.0000000, 0.0000000, 0.0000000}, {3.0000000, 2.5000000, 4.5000000},
      {1.0000000, 2.5000000, 4.5000000}, {1.0000000, 2.5000000, 3.5000000},
      {3.0000000, 2.5000000, 3.5000000}, {2.0000000, 3.5000000, 4.0000000}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expected_matrix.matrix[i][j] = exp_matrix_0[i][j];
    }
  }

  int ret = s21_eq_matrix(&expected_matrix, &result);
  ck_assert_int_eq(1, ret);

  s21_remove_matrix(&expected_matrix);
  s21_remove_matrix(&data->matrix_3d);
  for (int i = 0; i < data->sum_facets + 1; i++) {
    free(data->polygons[i].name_vertexes);
  }
  free(data->polygons);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_matrixToArray) {
  int count = 0;
  loading(data, str);
  matrixToArray(data);
  double expected_array[18] = {
      0.000000,  0.000000,  0.000000,  1.000000,  -0.500000, 0.500000,
      -1.000000, -0.500000, 0.500000,  -1.000000, -0.500000, -0.500000,
      1.000000,  -0.500000, -0.500000, 0.000000,  0.500000,  0.000000};

  for (int i = 0; i < (data->sum_vertexes + 1) * 3; i++) {
    if (data->array_3d[i] != expected_array[i]) {
      count++;
    }
  }
  ck_assert_int_eq(count, 0);
  for (int i = 0; i < data->sum_facets + 1; i++) {
    free(data->polygons[i].name_vertexes);
  }
  free(data->polygons);
}
END_TEST

START_TEST(test_arrayofstructureToArray) {
  int count = 0;
  loading(data, str);
  arrayofstructureToArray(data);
  int expected_array[12 * 2] = {1, 2, 2, 3, 3, 4, 4, 1, 1, 5, 5, 1,
                                2, 5, 5, 2, 3, 5, 5, 3, 4, 5, 5, 4};

  for (int i = 0; i < (data->v) * 2; i++) {
    if (data->indexes_array[i] != expected_array[i]) {
      count++;
    }
  }
  ck_assert_int_eq(count, 0);
  s21_remove_matrix(&data->matrix_3d);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, parser_test);
  tcase_add_test(tc1_1, test_rotation_about_x);
  tcase_add_test(tc1_1, test_rotation_about_y);
  tcase_add_test(tc1_1, test_rotation_about_z);
  tcase_add_test(tc1_1, test_scale);
  tcase_add_test(tc1_1, test_move);
  tcase_add_test(tc1_1, test_matrixToArray);
  tcase_add_test(tc1_1, test_arrayofstructureToArray);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return (0);
}
