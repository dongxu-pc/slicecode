void SnortHyperscanInit(struct _SnortConfig *sc, char *data, OptTreeNode *otn, int protocol)
{
    HyperscanData *hyperscan_data;
    OptFpList *fpl;
    void *hyperscan_dup;

    /*
     * allocate the data structure for pcre
     */
	/*
    pcre_data = (PcreData *) SnortAlloc(sizeof(PcreData));
    SnortPcreParse(sc, data, pcre_data, otn);
	*/
	hyperscan_data = (HyperscanData *)SnortAlloc(sizeof(HyperscanData));
	SnortHyperscanParse(sc, data, hyperscan_data, otn);

    otn->pcre_flag = 1;

    fpl = AddOptFuncToList(SnortPcre, otn);
    fpl->type = RULE_OPTION_TYPE_PCRE;

    if (add_detection_option(sc, RULE_OPTION_TYPE_PCRE, (void *)pcre_data, &pcre_dup) == DETECTION_OPTION_EQUAL)
    {
#ifdef DEBUG_RULE_OPTION_TREE
        LogMessage("Duplicate PCRE:\n%d %s\n%d %s\n\n",
            pcre_data->options, pcre_data->expression,
            ((PcreData *)pcre_dup)->options,
            ((PcreData *)pcre_dup)->expression);
#endif

        if (pcre_data->expression)
            free(pcre_data->expression);
        if (pcre_data->pe)
            free(pcre_data->pe);
        if (pcre_data->re)
            free(pcre_data->re);

        free(pcre_data);
        pcre_data = pcre_dup;
    }

    /*
     * attach it to the context node so that we can call each instance
     * individually
     */
    fpl->context = (void *) pcre_data;

    if (pcre_data->options & SNORT_PCRE_RELATIVE)
        fpl->isRelative = 1;

    if (otn->ds_list[PLUGIN_PCRE] == NULL)
        otn->ds_list[PLUGIN_PCRE] = (void *)pcre_data;

    return;
}
