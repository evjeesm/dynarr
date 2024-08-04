<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.11.0" doxygen_gitid="9b424b03c9833626cd435af22a444888fbbb192d">
  <compound kind="file">
    <name>dynarr.c</name>
    <path>src/</path>
    <filename>dynarr_8c.html</filename>
    <includes id="dynarr_8h" name="dynarr.h" local="yes" import="no" module="no" objc="no">dynarr.h</includes>
    <class kind="struct">dynarr_header_t</class>
    <member kind="function" static="yes">
      <type>static dynarr_opts_t</type>
      <name>get_opts</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a498b4e9fc56a6e87a6c5ca525026a9ed</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_t *</type>
      <name>dynarr_create_</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a99f1163f1932f71f0229a7340df68efb</anchor>
      <arglist>(const dynarr_opts_t *const opts)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>dynarr_get_ext_header</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a3acd4a1beb0e42a412b0482ddb6b9820</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_t *</type>
      <name>dynarr_clone</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a42427bb2220a4e0bf86a08717719a6a3</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dynarr_destroy</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>aebbaac3879771d77aa20068a26952197</anchor>
      <arglist>(dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dynarr_clear</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>afde94d3d24d33d8e81c3943db38a6327</anchor>
      <arglist>(dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>dynarr_size</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>af5c43e2644d185b9b01065af34ed6e29</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>dynarr_capacity</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a3ff11107726213a640d814b63cb123b2</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>dynarr_get</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a93c32dd116523090126d427cce08e114</anchor>
      <arglist>(const dynarr_t *const dynarr, const size_t index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dynarr_set</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a30d508a9f387e2227dd0d72a8bfd2a39</anchor>
      <arglist>(dynarr_t *const dynarr, const size_t index, const void *value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dynarr_set_zero</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a853ebc7310e119a0ebc946a404e0339a</anchor>
      <arglist>(dynarr_t *const dynarr, const size_t index)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>dynarr_first</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a559fc5ecc4687c6936ea890eeb1c79e2</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>dynarr_last</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a7ca5c94e8e78fae1860791386fa56ea6</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>dynarr_binary_find</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>aaf8dc0009bdab23da52ef7bcc5e754fd</anchor>
      <arglist>(const dynarr_t *const dynarr, const void *const value, const compare_t cmp, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>ssize_t</type>
      <name>dynarr_binary_find_index</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a8592e4d2a568f36dbcb1bce45a4b1460</anchor>
      <arglist>(const dynarr_t *const dynarr, const void *const value, const compare_t cmp, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_append</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a1e7f043863514d809cd6446053f6dc47</anchor>
      <arglist>(dynarr_t **const dynarr, const void *const value)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_prepend</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a4f3cc13065faeaa1b71f9b6c62ac7adf</anchor>
      <arglist>(dynarr_t **const dynarr, const void *const value)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_pop_back</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a3a36563e7efd7ad826fac165dd2a0d0c</anchor>
      <arglist>(dynarr_t **const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_pop_front</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a4ba384c69893f0961f0e71d6cd6be8fe</anchor>
      <arglist>(dynarr_t **const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_insert</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>ab449a79e6b33f55af35329df4363336e</anchor>
      <arglist>(dynarr_t **const dynarr, const size_t index, const void *value)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_spread_insert</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a00ddd61f7109ab9bb88da4fa5a88fb51</anchor>
      <arglist>(dynarr_t **const dynarr, const size_t index, const size_t amount, const void *const value)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>dynarr_binary_find_insert_place</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a5f6a46fc8cc0cfe14d98926cadbaa35d</anchor>
      <arglist>(const dynarr_t *const dynarr, const void *const value, const compare_t cmp, void *param)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_binary_insert</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>ac90d3742f1047b9b033a91e595d18ab9</anchor>
      <arglist>(dynarr_t **const dynarr, const void *const value, const compare_t cmp, void *param, size_t *const index)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_binary_reserve</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a20112ff4b2f14ef520353b23c10761de</anchor>
      <arglist>(dynarr_t **const dynarr, const void *const value, const compare_t cmp, void *const param, size_t *const index)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_remove</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>ae2e52e602d3867ce3e5fee688ea20263</anchor>
      <arglist>(dynarr_t **const dynarr, const size_t index)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_remove_range</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a1187f49d8bde19551b2c95ad430e596c</anchor>
      <arglist>(dynarr_t **const dynarr, const size_t index, const size_t amount)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_remove_if</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>aa975bac298720adfd05a978509081ada</anchor>
      <arglist>(dynarr_t **const dynarr, const predicate_t predicate, const size_t limit, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_t *</type>
      <name>dynarr_binary_merge</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a0bfdd0d8fbe0ca29ef26df50dc94f310</anchor>
      <arglist>(const dynarr_t *const first, const dynarr_t *const second, const compare_t cmp, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dynarr_foreach</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a2575dd307a95358e074e07c2b9999a9d</anchor>
      <arglist>(const dynarr_t *const dynarr, const foreach_t func, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dynarr_aggregate</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>ac18ed54e516f63ace336c4581f0e60c5</anchor>
      <arglist>(const dynarr_t *const dynarr, const aggregate_t func, void *const acc, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dynarr_transform</name>
      <anchorfile>dynarr_8c.html</anchorfile>
      <anchor>a8246d131a58a23f4d434775bd02bccb3</anchor>
      <arglist>(dynarr_t *const dynarr, const transform_t func, void *const param)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>dynarr.h</name>
    <path>src/</path>
    <filename>dynarr_8h.html</filename>
    <class kind="struct">dynarr_opts_t</class>
    <member kind="define">
      <type>#define</type>
      <name>DYNARR_DEFAULT_ARGS</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a7506aa30c586258bba10244e55492795</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>dynarr_create</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a1d05157f1911b8d089e57ca0696be01f</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>dynarr_status_t</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>ac2b2261a1330ac45a85883633d6a695d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>dynarr_t *</type>
      <name>dynarr_create_</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a99f1163f1932f71f0229a7340df68efb</anchor>
      <arglist>(const dynarr_opts_t *const opts)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>dynarr_get_ext_header</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a3acd4a1beb0e42a412b0482ddb6b9820</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_t *</type>
      <name>dynarr_clone</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a42427bb2220a4e0bf86a08717719a6a3</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dynarr_destroy</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>aebbaac3879771d77aa20068a26952197</anchor>
      <arglist>(dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dynarr_clear</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>afde94d3d24d33d8e81c3943db38a6327</anchor>
      <arglist>(dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>dynarr_size</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>af5c43e2644d185b9b01065af34ed6e29</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>dynarr_capacity</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a3ff11107726213a640d814b63cb123b2</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>dynarr_get</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a93c32dd116523090126d427cce08e114</anchor>
      <arglist>(const dynarr_t *const dynarr, const size_t index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dynarr_set</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a30d508a9f387e2227dd0d72a8bfd2a39</anchor>
      <arglist>(dynarr_t *const dynarr, const size_t index, const void *value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>dynarr_set_zero</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a853ebc7310e119a0ebc946a404e0339a</anchor>
      <arglist>(dynarr_t *const dynarr, const size_t index)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>dynarr_first</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a559fc5ecc4687c6936ea890eeb1c79e2</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>dynarr_last</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a7ca5c94e8e78fae1860791386fa56ea6</anchor>
      <arglist>(const dynarr_t *const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>dynarr_binary_find</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>aaf8dc0009bdab23da52ef7bcc5e754fd</anchor>
      <arglist>(const dynarr_t *const dynarr, const void *const value, const compare_t cmp, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>ssize_t</type>
      <name>dynarr_binary_find_index</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a8592e4d2a568f36dbcb1bce45a4b1460</anchor>
      <arglist>(const dynarr_t *const dynarr, const void *const value, const compare_t cmp, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_append</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a1e7f043863514d809cd6446053f6dc47</anchor>
      <arglist>(dynarr_t **const dynarr, const void *const value)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_prepend</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a4f3cc13065faeaa1b71f9b6c62ac7adf</anchor>
      <arglist>(dynarr_t **const dynarr, const void *const value)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_pop_back</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a3a36563e7efd7ad826fac165dd2a0d0c</anchor>
      <arglist>(dynarr_t **const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_pop_front</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a4ba384c69893f0961f0e71d6cd6be8fe</anchor>
      <arglist>(dynarr_t **const dynarr)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_insert</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>ab449a79e6b33f55af35329df4363336e</anchor>
      <arglist>(dynarr_t **const dynarr, const size_t index, const void *value)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_remove</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>ae2e52e602d3867ce3e5fee688ea20263</anchor>
      <arglist>(dynarr_t **const dynarr, const size_t index)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_remove_range</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a1187f49d8bde19551b2c95ad430e596c</anchor>
      <arglist>(dynarr_t **const dynarr, const size_t index, const size_t amount)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_remove_if</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>aa975bac298720adfd05a978509081ada</anchor>
      <arglist>(dynarr_t **const dynarr, const predicate_t predicate, const size_t limit, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_t *</type>
      <name>dynarr_binary_merge</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a0bfdd0d8fbe0ca29ef26df50dc94f310</anchor>
      <arglist>(const dynarr_t *const first, const dynarr_t *const second, const compare_t cmp, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_spread_insert</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a00ddd61f7109ab9bb88da4fa5a88fb51</anchor>
      <arglist>(dynarr_t **const dynarr, const size_t index, const size_t amount, const void *const value)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>dynarr_binary_find_insert_place</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a5f6a46fc8cc0cfe14d98926cadbaa35d</anchor>
      <arglist>(const dynarr_t *const dynarr, const void *const value, const compare_t cmp, void *param)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_binary_insert</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>ad2dd0b992152881697da2073a0c840d7</anchor>
      <arglist>(dynarr_t **const dynarr, const void *const value, const compare_t cmp, void *const param, size_t *const index)</arglist>
    </member>
    <member kind="function">
      <type>dynarr_status_t</type>
      <name>dynarr_binary_reserve</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a20112ff4b2f14ef520353b23c10761de</anchor>
      <arglist>(dynarr_t **const dynarr, const void *const value, const compare_t cmp, void *const param, size_t *const index)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dynarr_foreach</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a2575dd307a95358e074e07c2b9999a9d</anchor>
      <arglist>(const dynarr_t *const dynarr, const foreach_t func, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dynarr_aggregate</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>ac18ed54e516f63ace336c4581f0e60c5</anchor>
      <arglist>(const dynarr_t *const dynarr, const aggregate_t func, void *const acc, void *const param)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>dynarr_transform</name>
      <anchorfile>dynarr_8h.html</anchorfile>
      <anchor>a8246d131a58a23f4d434775bd02bccb3</anchor>
      <arglist>(dynarr_t *const dynarr, const transform_t func, void *const param)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>dynarr_header_t</name>
    <filename>structdynarr__header__t.html</filename>
  </compound>
  <compound kind="struct">
    <name>dynarr_opts_t</name>
    <filename>structdynarr__opts__t.html</filename>
    <member kind="variable">
      <type>size_t</type>
      <name>data_offset</name>
      <anchorfile>structdynarr__opts__t.html</anchorfile>
      <anchor>a6478b70c526a7158e1feefe1a3c34ea7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>size_t</type>
      <name>element_size</name>
      <anchorfile>structdynarr__opts__t.html</anchorfile>
      <anchor>a61aa2f610ed5a0202bd558522d04c7d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>size_t</type>
      <name>initial_cap</name>
      <anchorfile>structdynarr__opts__t.html</anchorfile>
      <anchor>ac6f8e73f613df4b4adb4f5162a301f47</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>grow_factor</name>
      <anchorfile>structdynarr__opts__t.html</anchorfile>
      <anchor>ae9243a6cf230d13c19c3e1eed2f78e61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>grow_threshold</name>
      <anchorfile>structdynarr__opts__t.html</anchorfile>
      <anchor>a387926f265aff246f24154f0bdbf731d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>shrink_threshold</name>
      <anchorfile>structdynarr__opts__t.html</anchorfile>
      <anchor>ab6ce4f5254ac3e20dc17c1648cb0605e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>alloc_param</name>
      <anchorfile>structdynarr__opts__t.html</anchorfile>
      <anchor>a52f2a199347e0b6eac57f14fac69abd9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Dynarr</title>
    <filename>index.html</filename>
    <docanchor file="index.html">md_README</docanchor>
  </compound>
</tagfile>
